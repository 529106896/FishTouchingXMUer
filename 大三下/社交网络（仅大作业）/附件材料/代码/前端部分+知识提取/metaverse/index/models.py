from django.db import models


# 创建book表
class WeiboData(models.Model):
    weibo_username = models.CharField(max_length=32, verbose_name='博主昵称')
    weibo_verification = models.CharField(max_length=32, verbose_name='微博认证', null='True', default='未认证')
    # TextField用于大文本
    weibo_content = models.TextField(verbose_name='微博内容')
    submit_time = models.TextField(verbose_name='发布时间')
    forward_counts = models.IntegerField(default=0, verbose_name='转发数')
    comments_counts = models.IntegerField(default=0, verbose_name="评论数")
    points_times = models.IntegerField(default=0, verbose_name='点赞数')

    def __str__(self):
        return self.weibo_username + " " + self.submit_time


class UserInfo(models.Model):
    username = models.CharField(max_length=24, verbose_name="用户名")
    password = models.CharField(max_length=24, verbose_name="密码")

    def __str__(self):
        return self.username + " " + self.password
