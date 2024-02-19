import os

from django.core.paginator import Paginator, PageNotAnInteger, EmptyPage
from django.http import HttpResponse
from django.shortcuts import render
from django.template import Template, Context
from hanlp import *
import jiagu

from index.models import WeiboData


# class testClass:
#     def Web_name(self):
#         return "这是一个类"
#
#
# def return_hello():
#     return "欢迎来到C语言中文网"
#
#
# def test_html(request):
#     a = {'name': '大西瓜',
#          'course': ['Python', 'Java', 'C++'],
#          'b': {"name": "fuckyou", "address": "映雪三208"},
#          'test_hello': return_hello(),
#          'class_obj': testClass()
#          }
#     return render(request, 'testHtml.html', a)
#
#
# def test_if(request):
#     dic = {'x': -5}
#     return render(request, 'testIf.html', dic)
#
#
# def test_Web(request):
#     t = Template(
#         """
#     {% if web.name == 'C语言中文网' %}
#         {% if printable %}
#             <h1>{{ printable }}</h1>
#             <h1>Hello C语言中文网</h1>
#         {% else %}
#             <h2>{{ printable }}</h2>
#             <h2>欢迎您下次访问</h2>
#         {% endif %}
#     {% endif %}
#     """)
#     # Context必须是字典类型的对象，用于给模板传递数据
#     c = Context({'web': {'name': "C语言中文网"}, 'printable': True})
#     html = t.render(c)
#     return HttpResponse(html)
#
#
# def test_for(request):
#     dic = {'list': ["XMU", "PKU", "TSU"]}
#     return render(request, 'testFor.html', dic)
#
#
# def test_url(request):
#     return render(request, 'test_url.html')
#
#
# def weibodataShow(request):
#     weibodataList = WeiboData.objects.all()
#     paginator = Paginator(weibodataList, 20)
#     totalPages = paginator.num_pages
#     page = request.GET.get('page')
#     datalist = []
#     if page:
#         datalist = paginator.page(page).object_list
#     else:
#         datalist = paginator.page(1).object_list
#         page = 1
#
#     try:
#         page_object = paginator.page(page)
#     except PageNotAnInteger:
#         page_object = paginator.page(1)
#     except EmptyPage:
#         page_object = paginator.page(paginator.num_pages)
#     return render(request, 'weiboDataShow.html', {
#         'page_object': page_object,
#         'data_list': datalist,
#         'page': page,
#         'total': totalPages
#     })

def index(request):
    weibodataList = WeiboData.objects.all()[:1000]
    return render(request, 'index.html', {
        'data_list': weibodataList,
    })

# def returnImage(request):
#     selected = request.GET.get('cluster')
#     if selected is not None:
#         imgUrl = 'images/cluster=' + selected + ".png"
#     else:
#         imgUrl = ''
#     return render(request, 'clusterResult.html', {
#         'imgUrl': imgUrl,
#         'currentOption': selected
#     })


# def returnWordCloudImg(request):
#     selected = request.GET.get('type')
#     print(selected)
#     if selected is not None:
#         imgUrl = 'images/wordCloud' + selected + ".png"
#     else:
#         imgUrl = ''
#     return render(request, 'wordCloud.html', {
#         'imgUrl': imgUrl,
#         'currentOption': selected
#     })


def goToCountLDA(request):
    return render(request, 'count_lda_pass5.html')

def goToTFIDF(request):
    return render(request, 'tfidf_lda_pass5.html')

# def getText(request):
#     request.encoding='utf-8'
#
#     ctx ={}
#
#     if request.POST.get('q'):
#        text = request.POST.get('q')
#     else:
#         text=' '
#
#     ctx['input'] =text
#
#     #hanlp 命名实体识别
#     segment = HanLP.newSegment()
#     hanlp = segment.seg(text)
#     print(hanlp)
#     hanlpNer = {}
#     hPname = []
#     hLname = []
#     hIname = []
#     for i in hanlp:
#         strN = str(i)
#         res = strN.split("/")
#         hanlpNer[res[0]] = res[1]
#     for key in hanlpNer:
#         temp = hanlpNer.get(key)
#         if temp.startswith('nr'):
#             hPname.append(key)
#         if temp.startswith('ns'):
#             hLname.append(key)
#         if temp.startswith('ni') or temp.startswith('nt'):
#             hIname.append(key)
#     ctx['hPname'] = hPname
#     ctx['hLname'] = hLname
#     ctx['hIname'] = hIname
#
#     #jiagu
#     words = jiagu.seg(text) # 分词
#     print(words)
#     pos = jiagu.pos(words) # 词性标注
#     print(pos)
#     ner = jiagu.ner(words) # 命名实体识别
#     print(ner)
#     knowledge = jiagu.knowledge(text) #关系抽取
#     print(knowledge)
#     relationExtraction = []
#     for i in knowledge:
#         strR = ''
#         strR = strR+str(i[0])+'的'+str(i[1])+'是'+str(i[2])
#         relationExtraction.append(strR)
#
#
#     dictionary = dict(zip(words,ner))
#     Pname = []
#     Lname = []
#     Iname = []
#
#     for key in dictionary:
#         if dictionary.get(key) == 'B-PER' or dictionary.get(key) == 'B-IER':
#             Pname.append(key)
#         if dictionary.get(key) == 'B-LOC' or dictionary.get(key) == 'I-LOC':
#             Lname.append(key)
#         if dictionary.get(key) == 'B-ORG' or dictionary.get(key) == 'I-ORG':
#             Iname.append(key)
#     ctx['Pname'] = Pname
#     ctx['Lname'] = Lname
#     ctx['Iname'] = Iname
#
#     if request.POST:
#         ctx['text'] = request.POST['q']
#     ctx['views_list'] =  relationExtraction
#
#     return render(request, "get_form.html", ctx)

def goToSentiment(request):
    return render(request, 'sentiment.html')