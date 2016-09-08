#include "inexor/flowgraph/memory/bool/fl_mem_bool.hpp"

namespace inexor {
namespace vscript {

    CMemBoolNode::CMemBoolNode(vec position, bool start_value, bool constant_memory)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_MEMORY_BOOL;
        pos = position;   
        block.type = INEXOR_VSCRIPT_DATA_TYPE_BOOLEAN;
        block.data.bool_value = start_value;
        block.constant_value = constant_memory;
    }

    CMemBoolNode::~CMemBoolNode()
    {
    }

    void CMemBoolNode::render_additional()
    {
        // render the current integer value
        vec p = pos;
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));

        // this is a great C++11 feature!
        if (block.data.bool_value) additional_particle_text = "true";
        else additional_particle_text = "false";
        particle_text(p + vec(0,0,2.0f), additional_particle_text.c_str(), PART_TEXT, 1, INEXOR_VSCRIPT_COLOR_TRIGGERED, 1.0f);
        if(block.constant_value)
        {
            particle_text(p + vec(0,0,3.0f), "constant value", PART_TEXT, 1, INEXOR_VSCRIPT_COLOR_PENDING, 1.0f);
        }
    }

    void CMemBoolNode::set_value(bool set_value)
    {
        last_time = this_time;
        if(block.constant_value)
        {
            triggered_color = INEXOR_VSCRIPT_COLOR_PENDING;
            conoutf(CON_DEBUG, "[3DVS-bool-setvalue] can't change constant boolean value!");
        }
        else block.data.bool_value = set_value;
    }


    bool CMemBoolNode::get_value()
    {
        return block.data.bool_value;
    }

};
};