#!/usr/bin/env perl
my $blanked = 0;
open (IN, "xscreensaver-command -watch |");
while (<IN>) {
    if (m/^(BLANK|LOCK)/) {
        if (!$blanked) {
            `/home/lgbland/code/znc/landon_away_log/away.sh`;
            print scalar localtime.": away logging enabled\n";
            $blanked = 1;
        }
    } elsif (m/^UNBLANK/) {
        `/home/lgbland/code/znc/landon_away_log/back.sh`;
        print scalar localtime.": away logging disabled\n";
        $blanked = 0;
    }
}
