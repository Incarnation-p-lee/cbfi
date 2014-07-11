#!/usr/bin/perl
use strict;
use 5.010;


my $basedir = '.';
my $sdir = './src';
# format: k->v, module name -> included files
my %module_files;


if($#ARGV != -1){
  $sdir = '.';
  foreach(@ARGV){
    chomp;
    process_module($_);
  }
}else{
  &build_md_map($basedir);                     # build hash map %module_files
  &update_declare();                           # update all modules
}

sub build_md_map{
  my $base = shift @_;
  opendir BASE_DIR, $base or 
    die "Failed to open directory [$base].  $!";
  
  foreach(readdir BASE_DIR){
    if(/\w+\.m\b/){
      my $mname = $_;
      open MD_FILE, '<', $mname, or 
        die "Failed to open file [$mname].  $!";

      my $files;
      while(<MD_FILE>){
        chomp;
        if(/#include/){
          if(/"(\w+\.[c|h])"/){
            $files .= ' ' . $1;
          }
        }
      }

      $module_files{$mname} = $files;
      close(MD_FILE);
    }
  }

  closedir(BASE_DIR);
}


sub update_declare{
  my @mod = keys %module_files;
  my @smod = sort @mod;
  foreach(@smod){
    &process_module($module_files{$_});
  }
}


sub process_module{
  my $fn = shift @_;
  my @files = split / /, $fn;
  my @head;
  my @source;
  foreach(@files){
    unshift @head, $_ if m/\w+\.h/;
    unshift @source, $_ if m/\w+\.c/;
  }

  my @ssource = sort @source;
  foreach(@ssource){
    say "\nOperating on [$_] ...";
    my $fullname = $sdir . '/' . $_;
    open SFILE, '<', $fullname or 
      die "Failed to open file [$fullname].  $!";
    
    my $comments = undef; 
    while(<SFILE>){
      next if $comments;

      next if /\/\//;
      if(/\/\*/){
        $comments = 'y' unless /\*\//;
        next;
      }
      if(/\*\//){
        say "CCC";
        $comments = undef;
        next;
      }

      next if /;|:/;
      next if /,\s*$/;
      next if /{|}/;
      next if /\b(for|while|switch|if|else if)\(/;
      next if /\belse/;
      next if /#ifdef|#endif/;
      next if /^\s*$/;
      #say "=== $_";
      my $single = $_;
      while(<SFILE>){
        $single .= $_;
        last if /\)\s*$/;
      }
      $single = undef if $single =~ /;/;
      if($single){
        my $decl = &def_to_decl($single);
        say $decl;
      }
    }

    close(SFILE);
  }
}


sub def_to_decl{
  my $def = shift @_;
  chomp $def;
  $def .= ';';
  return $def if $def =~ /\(\s*void\s*\)/;

  if($def =~ /,/){
    $def =~ s/(\w+)(\**)\s+(\*+)\w+,/\1 \2\3,/g if $def =~ /\*/;
    $def =~ s/(\w+)\s+\w+,/\1,/g;
  }
  $def =~ s/\s*\w+\)/)/g;
  return $def;
}
