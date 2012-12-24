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

    // Module first load
    virtual bool OnLoad(const CString& sArgs, CString& sMessage) {
        away = false;

        // Setup the away commands
        CModule::AddCommand("away", static_cast<CModCommand::ModCmdFunc>(&LandonAwayLog::SetAway));
        CModule::AddCommand("back", static_cast<CModCommand::ModCmdFunc>(&LandonAwayLog::SetBack));

        return true;
    }

    // Set status to away. sLine is unused, but requried to give this as
    // a function pointer to AddCommand()
    void SetAway(const CString& sLine) {
        away = true;
        PutModule("Set to away");
    }

    // Set status to not away. sLine is unused, but requried to give this as
    // a function pointer to AddCommand()
    void SetBack(const CString& sLine) {
        away = false
        savedMessages.clear();
        PutModule("No longer away");
    }

    // Save PMs if away
    virtual EModRet OnPrivMsg(CNick& Nick, CString& sMessage) {
        if(away == true)
            savedMessages.push_back("<" + Nick.GetNick() + "> " + sMessage);
        return CONTINUE;
    }

    // When a client logs in, send them any saved messages we have
    // Once the messages have been relayed once, clear them so
    // that they don't get continually sent (if a phone is constently
    // disconnecting and reconnection for example)
    virtual void OnClientLogin() {
        if(away == true) {
            for (unsigned i=0; i<savedMessages.size(); i++) {
                PutModule(savedMessages.at(i));
            }
            savedMessages.clear();
        }
    }

private:
    bool away;                  // Flag for if you are away
    std::vector<CString> savedMessages;  // Saved messages
};

template<> void TModInfo<LandonAwayLog>(CModInfo& Info) {
    Info.AddType(CModInfo::NetworkModule);
    Info.AddType(CModInfo::GlobalModule);
    Info.SetHasArgs(false);
}

USERMODULEDEFS(LandonAwayLog, "Save and deliver PMs on connect while marked as away")
