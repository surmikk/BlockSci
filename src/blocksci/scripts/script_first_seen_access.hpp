//
//  script_first_seen_access.hpp
//  blocksci
//
//  Created by Harry Kalodner on 8/1/17.
//
//

#ifndef script_first_seen_access_hpp
#define script_first_seen_access_hpp

#include "script_info.hpp"
#include <blocksci/file_mapper.hpp>

namespace blocksci {
    
    struct DataConfiguration;
    
    template<auto>
    struct ScriptFirstSeenFile : public FixedSizeFileMapper<uint32_t> {
        using FixedSizeFileMapper<uint32_t>::FixedSizeFileMapper;
    };
    
    class ScriptFirstSeenAccess {
        using ScriptFilesFirstSeenTuple = apply_template_t<ScriptFirstSeenFile, ScriptInfoList>;
        ScriptFilesFirstSeenTuple scriptFilesFirstSeen;
        
    public:
        
        ScriptFirstSeenAccess(const DataConfiguration &config);
        
        void reload();
        
        template <ScriptType::Enum type>
        uint32_t getFirstTxNum(uint32_t addressNum) const {
            auto &file = std::get<ScriptFirstSeenFile<type>>(scriptFilesFirstSeen);
            return *file.getData(addressNum - 1);
        }
    };
    
}

#endif /* script_first_seen_access_hpp */
