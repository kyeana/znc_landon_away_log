znc_landon_away_log
===================
A simple znc module which lets you manually toggle your 'away' status.

If you are marked as away, then all PMs will be saved, and when a client 
connects to znc those messages will be sent to this client (and the messages cleared). 
When the status is set to no longer away those saved messages will be discarded and 
no further messages will be saved until the away status is toggled again.

Setting the away status is done via '/msg *away away'. Removing the away status is
done via '/msg *away back'.
