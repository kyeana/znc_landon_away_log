/*
 * Copyright (C) 2008-2012  See the AUTHORS file for details.
 * Copyright (C) 2006-2007, CNU <bshalm@broadpark.no> (http://cnu.dieplz.net/znc)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#include <znc/FileUtils.h>
#include <znc/User.h>
#include <znc/IRCNetwork.h>
#include <znc/Chan.h>
#include <znc/Server.h>

class LandonAwayLog: public CModule {
public:
    MODCONSTRUCTOR(LandonAwayLog) {}

    // Set the away status
    void SetAwayStatus();

    // Module first load
    virtual bool OnLoad(const CString& sArgs, CString& sMessage);

    // On PM handler
    virtual EModRet OnPrivMsg(CNick& Nick, CString& sMessage);

    // When a client lgos in, send them any saved messages we have
    virtual void CModule::OnClientLogin();

    // TODO - have commands to this module to set the away status

private:
    bool away;                  // Flag for if you are away
    std::vector savedMessages;  // Saved messages
};

bool LandonAwayLog::OnLoad(const CString& sArgs, CString& sMessage) {
    away = false;
}

void LandonAwayLog::SetAwayStatus(bool status) {
    away = status;
    if(away == false)
        savedMessages.clear();
}

void LandonAwayLog::OnClientLogin() {
    if(away == true) {
        for (unsigned i=0; i<savedMessages.size(); i++) {
            CModule::PutModNotice(savedMessages.at(i));
        }
    }
}

CModule::EModRet LandonAwayLog::OnPrivMsg(CNick& Nick, CString& sMessage) {
    // If the pm comes from this log, ignore it so we don't get compound away messages
    if(Nick.GetNick() != 'landon_away_message') {
        savedMessages.push_back("<" + Nick.GetNick() + "> " + sMessage);
    }
    return CONTINUE;
}

template<> void TModInfo<LandonAwayLog>(CModInfo& Info) {
    Info.AddType(CModInfo::NetworkModule);
    Info.AddType(CModInfo::GlobalModule);
    Info.SetHasArgs(false);
}

USERMODULEDEFS(LandonAwayLog, "Save PM's while marked as away")
