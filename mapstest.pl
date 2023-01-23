#!/usr/bin/env perl

use v5.16.2;
use warnings;

use File::Temp qw( tempfile tempdir );
use File::Copy qw( copy );
use Cwd        qw(getcwd);

my $current_dir = getcwd();

# define utility subroutines
sub strip {
    my ($str) = @_;
    return $str =~ s/^\s*(.*)\s*$/$1/r;
}

# get command-line arguments
@ARGV == 3 or die <<"EOS";
$0: the number of command-line arguments must be 3
usage: $0 COMPILER SOURCE GLOBLMEM
EOS

my ( $compiler_path, $source_path, $globlmem_path ) = @ARGV;

# make temporary directory
my $working_dir = tempdir( 'mapstest.XXXXXXXX', TMPDIR => 1, CLEANUP => 1 );

# compile test program
my ( undef, $asm_path )
    = tempfile( 'XXXXXXXX', SUFFIX => '.s', DIR => $working_dir, OPEN => 0 );
open( my $compiler_out_fh, '-|', "$compiler_path < $source_path > $asm_path" )
    or die "cannot execute $compiler_path: $!";
close($compiler_out_fh) or die "$compiler_path: $!";

# run maps
chdir($working_dir) or die "cannot chdir $working_dir: $!";

open( my $maps_out_fh, '-|', "maps -e -q $asm_path" )
    or die "cannot execute maps: $!";
my $inst_count = do {
    my @maps_out   = <$maps_out_fh>;
    my @match      = grep( /total inst\. count:\s*[0-9]+$/, @maps_out );
    my $inst_count = shift(@match);
    ${^MATCH} if $inst_count =~ m/([0-9])+/p;
};

close($maps_out_fh) or die "maps: $!";

chdir($current_dir) or die "cannot chdir $current_dir: $!";

# check global memory
my $mem_path = "$asm_path.mem";

open( my $globlmem_fh, '<', $globlmem_path )
    or die "cannot open $globlmem_path: $!";

open( my $mem_fh, '<', $mem_path ) or die "cannot open $mem_path: $!";
my @mem_lines = <$mem_fh>;
close($mem_fh) or die "cannot close $mem_path: $!";

my $pass = 1;
while ( my $line = <$globlmem_fh> ) {
    $line = strip($line);
    my ( $address, $correct_value ) = split( /=/, $line );
    my $address_qword = $address =~ s/.$/0/r;
    my @matched_lines = grep( /^$address_qword:/, @mem_lines );
    my $qword_line    = shift(@matched_lines);

    my $target_value;
    if ( !$qword_line ) {
        $target_value = '00000000';
    }
    else {
        $qword_line =~ s/^.*:\s*(.*)\s*/$1/;
        my @qword = split( / /, $qword_line );
    SWITCH: {
            $_ = $address;
            if (/^.*0$/) { $target_value = $qword[0]; last SWITCH; }
            if (/^.*4$/) { $target_value = $qword[1]; last SWITCH; }
            if (/^.*8$/) { $target_value = $qword[2]; last SWITCH; }
            if (/^.*c$/) { $target_value = $qword[3]; last SWITCH; }
            say "unexpected address $address at $globlmem_path line $.";
            exit 2;
        }
    }

    if ( $target_value eq $correct_value ) {
        say "$target_value at $address, pass, $inst_count insts. executed";
    }
    else {
        say "$target_value at $address, expected $correct_value";
        $pass = 0;
    }
}

close($globlmem_fh) or die "cannot close $globlmem_path: $!";

exit 1 unless $pass;
