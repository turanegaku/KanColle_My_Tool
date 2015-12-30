#!/usr/bin/env python
# -*- coding: utf-8 -*-

import json
d = json.load(
    open("/Users/turane_gaku/scripts/KanColle_My_Tool/data/api_start2"))


def p_keys():
    for k in sorted(d):
        print k

def p_slotitem():
    for l in d['api_mst_slotitem']:
        for k in l:
            if type(l[k]) == type(u''):
                print k, l[k].encode('utf-8'),
            else:
                print k, l[k],
            if k == 'api_type':
                print [v['api_name'] for v in d['api_mst_slotitem_equiptype'] if v['api_id'] == l['api_type'][2]][0].encode('utf-8'),
            print
        print

def p_slotitem_equiptype():
    for l in d['api_mst_slotitem_equiptype']:
        for k in l:
            if type(l[k]) == type(u''):
                print k, l[k].encode('utf-8')
            else:
                print k, l[k]
        print

def p_ship():
    for l in d['api_mst_ship']:
        for k in l:
            if type(l[k]) == type(u''):
                print k, l[k].encode('utf-8'),
            else:
                print k, l[k],
            if k == 'api_stype':
                print d['api_mst_stype'][l[k] - 1]['api_name'].encode('utf-8'),
            print
        print

def p_shiptype():
    for l in d['api_mst_stype']:
        for k, v in l.items():
            if k == 'api_equip_type':
                print k,
                for i in [i for i in sorted(map(int, v.keys())) if v[str(i)]]:
                    print i, [v['api_name'] for v in d['api_mst_slotitem_equiptype'] if v['api_id'] == i][0].encode('utf-8'),
                print
            else:
                if type(v) == type(u''):
                    print k, v.encode('utf-8')
                else:
                    print k, l[k]
        print
