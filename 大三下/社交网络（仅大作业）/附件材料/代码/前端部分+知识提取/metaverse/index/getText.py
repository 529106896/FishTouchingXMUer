from django.http import HttpResponse
from django.shortcuts import render
import jiagu
from pyhanlp import *
import os
 
# 接收请求数据
def getText(request):  
    request.encoding='utf-8'

    ctx ={}

    if request.POST.get('q'):
       text = request.POST.get('q')
    else:
        text=' '

    ctx['input'] =text

    #hanlp 命名实体识别
    segment = HanLP.newSegment()
    hanlp = segment.seg(text)
    print(hanlp)
    hanlpNer = {}
    hPname = []
    hLname = []
    hIname = []
    for i in hanlp:
        strN = str(i)
        res = strN.split("/")
        hanlpNer[res[0]] = res[1]
    for key in hanlpNer:
        temp = hanlpNer.get(key)
        if temp.startswith('nr'):
            hPname.append(key)
        if temp.startswith('ns'):
            hLname.append(key)
        if temp.startswith('ni') or temp.startswith('nt'):
            hIname.append(key) 
    ctx['hPname'] = hPname   
    ctx['hLname'] = hLname  
    ctx['hIname'] = hIname
    ctx['dict'] = hanlpNer                             

    #jiagu
    words = jiagu.seg(text) # 分词
    print(words)
    pos = jiagu.pos(words) # 词性标注
    #print(pos)
    ner = jiagu.ner(words) # 命名实体识别
    #print(ner)
    knowledge = jiagu.knowledge(text) #关系抽取
    print(knowledge)
    relationExtraction = []
    for i in knowledge:
        strR = ''
        strR = strR+str(i[0])+'的'+str(i[1])+'是'+str(i[2])
        relationExtraction.append(strR)


    dictionary = dict(zip(words,ner))
    Pname = []
    Lname = []
    Iname = []

    for key in dictionary:
        if dictionary.get(key) == 'B-PER' or dictionary.get(key) == 'B-IER':
            Pname.append(key)
        if dictionary.get(key) == 'B-LOC' or dictionary.get(key) == 'I-LOC':
            Lname.append(key)
        if dictionary.get(key) == 'B-ORG' or dictionary.get(key) == 'I-ORG':
            Iname.append(key)           
    ctx['Pname'] = Pname   
    ctx['Lname'] = Lname  
    ctx['Iname'] = Iname      

    if request.POST:
        ctx['text'] = request.POST['q']
    ctx['views_list'] =  relationExtraction

    return render(request, "get_form.html", ctx)