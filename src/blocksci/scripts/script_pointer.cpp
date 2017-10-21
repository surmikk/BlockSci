//
//  script_pointer.cpp
//  blocksci
//
//  Created by Harry Kalodner on 9/19/17.
//
//

#include "script_pointer.hpp"
#include "address/address_info.hpp"
#include "address/address.hpp"
#include "script_info.hpp"
#include "script.hpp"
#include "scripts.hpp"

#include <boost/variant.hpp>

namespace blocksci {
    ScriptPointer::ScriptPointer(const Address &address) : ScriptPointer(address.addressNum, scriptType(address.type)) {}
    
    std::string ScriptPointer::toString() const {
        if (scriptNum == 0) {
            return "InvalidScriptPointer()";
        } else {
            std::stringstream ss;
            ss << "ScriptPointer(";
            ss << "scriptNum=" << scriptNum;
            ss << ", type=" << scriptName(type);
            ss << ")";
            return ss.str();
        }
    }
    
    ScriptVariant ScriptPointer::getScript(const ScriptAccess &access) const {
        if (scriptNum == 0) {
            throw std::runtime_error("Tried to get script for bad address");
        }
        return Script::create(access, *this);
    }
    
    std::ostream &operator<<(std::ostream &os, const ScriptPointer &scriptPointer) {
        os << scriptPointer.toString();
        return os;
    }
}
