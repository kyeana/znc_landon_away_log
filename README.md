znc_landon_away_log
===================
A simple znc module which lets you manually toggle your 'away' status.

If you are marked as away, then all PMs will be saved, and evertime a client 
connects to znc those messages will be sent to this client. When the status
is set to no longer away those saved messages will be discarded and no further
messages will be saved until the away status is toggled again.
