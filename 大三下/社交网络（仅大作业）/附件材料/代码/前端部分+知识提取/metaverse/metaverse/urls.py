"""metaverse URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from index import getText
from index import views

urlpatterns = [
    # 这个表示，将admin/的路径映射到哪个文件
    path('admin/', admin.site.urls, name='admin'),
    # path('weibodataShow/', views.weibodataShow, name='weiboIndex'),
    # path('clusterimg/', views.returnImage, name='imgtest'),
    # path('wordCloudImg/', views.returnWordCloudImg, name='wordCloud'),
    path('index/', views.index, name='index'),
    path('countLDA/', views.goToCountLDA, name='countLDA'),
    path('getText/', getText.getText,name='know'),
    path('sentiment/', views.goToSentiment, name='sentiment'),
    path('tfidfLDA/', views.goToTFIDF, name='tfidfLDA')
]
