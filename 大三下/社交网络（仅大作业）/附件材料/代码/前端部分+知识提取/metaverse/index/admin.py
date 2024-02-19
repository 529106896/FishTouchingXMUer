from django.contrib import admin
from django.urls import path

from index.models import *
from import_export import resources
from import_export.admin import ImportExportModelAdmin


class WeiboResource(resources.ModelResource):
    class Meta:
        model = WeiboData
        export_order = ['weibo_username', 'weibo_verification', 'weibo_content', 'submit_time', 'forward_counts',
                        'comments_counts', 'points_times']


# 使用装饰器来把模型类和管理类进行关联
@admin.register(WeiboData)
class WeiboAdmin(ImportExportModelAdmin):
    # 在默认的情况下，Model 在 admin 列表修改页（Admin ChangeList）只会显示一列，内容是实例对象的__str__的返回值
    # 可以通过 list_display 属性来实现多现实一些东西
    list_display = ['id', 'weibo_username', 'weibo_verification', 'weibo_content', 'submit_time', 'forward_counts',
                    'comments_counts', 'points_times']
    # 给指定的字段添加搜索框
    search_fields = ['weibo_username', 'weibo_content']
    # 过滤器
    # list_filter = ['weibo_username', 'weibo_content']
    # 对应字段是否链接到列表页面
    list_display_links = ['weibo_username', 'weibo_content']
    # 允许某些字段在列表页面上就可以编辑
    list_editable = ['weibo_verification', 'forward_counts', 'comments_counts', 'points_times']
    resource_class = WeiboResource
    # change_list_template = 'templates/test.html'

    # def get_urls(self):
    #     urls = super().get_urls()
    #     my_urrls = [
    #         path('ciyun1/', self)
    #     ]

# 这个方法用来注册需要管理的类
# admin.site.register([WeiboData, UserInfo])
