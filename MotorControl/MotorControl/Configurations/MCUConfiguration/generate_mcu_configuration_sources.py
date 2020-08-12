#!/bin/python
from sys import argv
import json


std_header = """/****************************************************************************/
/* Copyright 2020 by Tikhonov A. All rights reserved.                      */
/****************************************************************************/

// This file is generated automatically. Don't edit it!
"""




def gen_settings(obj):
    
    head_str = std_header
    head_str += '\n\n'

    head_str+= 'private: \n\n'

    for s in obj:
        head_str+= '        '+s['type']+' m_'+s['name']+';                      //' + s['comment'] + '\n'

    head_str += 'public:\n\n'

    for s in obj:
        head_str += '    //' + s['comment'] + '\n'
        head_str += '    virtual '+s['type']+' get_'+s['name']+'(void) const { return ' + ' m_'+s['name'] + '; }\n\n'

    out = open('stm32_configuration_gen.h','w')
    out.write(head_str)
    out.close()



with open('STM32Configuration.json', 'rt') as cmd_f:
    obj = json.loads(cmd_f.read().replace('\n', ''))
    gen_settings(obj)
