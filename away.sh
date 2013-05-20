#!/bin/bash
echo -e "PASS <password>\n NICK awaybot\n USER <user>\n PRIVMSG *awaystore :away\n QUIT" | openssl s_client -connect irc.host.com:<port> -quiet > /dev/null 2>&1
