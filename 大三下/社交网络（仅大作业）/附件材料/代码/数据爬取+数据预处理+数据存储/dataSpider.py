# -*- coding: utf-8 -*-
import time
import datetime
import re
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import xlwt

driver = webdriver.Chrome()

# ********************************************************************************
#                            第一步: 登陆login.sina.com
#                     这是一种很好的登陆方式，有可能有输入验证码
#                          登陆之后即可以登陆方式打开网页
# ********************************************************************************

def LoginWeibo(username, password):
    try:
        # 输入用户名/密码登录
        print('准备登陆Weibo.cn网站...')
        driver.get("http://login.sina.com.cn/")
        elem_user = driver.find_element_by_name("username")
        elem_user.send_keys(username)  # 用户名
        elem_pwd = driver.find_element_by_name("password")
        elem_pwd.send_keys(password)  # 密码
        elem_sub = driver.find_element_by_xpath("//input[@class='W_btn_a btn_34px']")
        elem_sub.click()  # 点击登陆 因无name属性

        try:
            # 输入验证码
            time.sleep(15)
            elem_sub.click()
        except:
            # 不用输入验证码
            pass

        # 获取Coockie 推荐资料：http://www.cnblogs.com/fnng/p/3269450.html
        print('Crawl in ', driver.current_url)
        print('输出Cookie键值对信息:')
        for cookie in driver.get_cookies():
            print(cookie)
            for key in cookie:
                print(key, cookie[key])
        print('登陆成功...')
    except Exception as e:
        print("Error: ", e)
    finally:
        print('End LoginWeibo!\n')


# ********************************************************************************
#                  第二步: 访问http://s.weibo.com/页面搜索结果
#               输入关键词、时间范围，得到所有微博信息、博主信息等
#                     考虑没有搜索结果、翻页效果的情况
# ********************************************************************************

def GetSearchContent(key):
    driver.get("http://s.weibo.com/")
    print('搜索热点主题：')
    time.sleep(5)
    # 输入关键词并点击搜索
    item_inp = driver.find_element_by_xpath("//input[@node-type='text']")
    item_inp.send_keys(key)
    item_inp.send_keys(Keys.RETURN)  # 采用点击回车直接搜索

    time.sleep(5)
    # 获取搜索词的URL，用于后期按时间查询的URL拼接
    current_url = driver.current_url
    current_url = current_url.split('&')[0]

    global start_stamp
    global page


    # 需要抓取的开始和结束日期，可根据你的实际需要调整时间
    # start_date = datetime.datetime(2022, 1, 11)
    start_date = datetime.datetime(2021, 9, 1)
    end_date = datetime.datetime(2022, 5, 15)
    delta_date = datetime.timedelta(days=1)

    # 每次抓取一天的数据
    start_stamp = start_date
    end_stamp = start_date + delta_date

    global outfile
    global sheet

    outfile = xlwt.Workbook(encoding='utf-8')

    while end_stamp <= end_date:
        page = 1

        # 每一天使用一个sheet存储数据
        sheet = outfile.add_sheet(start_stamp.strftime("%Y-%m-%d-%H"))
        initXLS()
        # 通过构建URL实现每一天的查询
        url = current_url + '&typeall=1&suball=1&timescope=custom:' + start_stamp.strftime(
                "%Y-%m-%d-%H") + ':' + end_stamp.strftime("%Y-%m-%d-%H") + '&Refer=g'
        driver.get(url)
        handlePage()  # 处理当前页面内容

        start_stamp = end_stamp
        end_stamp = end_stamp + delta_date


# time.sleep(1)

def handlePage():
    while True:
        # 之前认为可能需要sleep等待页面加载，后来发现程序执行会等待页面加载完毕
        # sleep的原因是对付微博的反爬虫机制，抓取太快可能会判定为机器人，需要输入验证码
        time.sleep(1)
        # 先行判定是否有内容
        if checkContent() and page <= 50:
            print("getContent")
            getContent()
            # 先行判定是否有下一页按钮
            if checkNext():
                # 拿到下一页按钮
                next_page_btn = driver.find_element_by_css_selector("#pl_feedlist_index > div.m-page > div > a.next")
                next_page_btn.click()
            else:
                print("no Next")
                break
        else:
            print("no Content")
            break

# 判断页面加载完成后是否有内容
def checkContent():
    # 有内容的前提是有“导航条”？错！只有一页内容的也没有导航条
    # 但没有内容的前提是有“pl_noresult”
    try:
        driver.find_element_by_xpath("//div[@class='card card-no-result s-pt20b40']")
        flag = False
    except:
        flag = True
    return flag

# 判断是否有下一页按钮
def checkNext():
    try:
        driver.find_element_by_css_selector("#pl_feedlist_index > div.m-page > div > a.next")
        flag = True
    except:
        flag = False
    return flag


# 判断是否有展开全文按钮
def checkqw():
    try:
        driver.find_element_by_xpath(".//div[@class='content']/p[@class='txt']/a")
        flag = True
    except:
        flag = False
    return flag


# 在添加每一个sheet之后，初始化字段
def initXLS():
    name = ['博主昵称', '微博认证', '微博内容','发布时间', '转发', '评论','赞']

    global row
    global outfile
    global sheet

    row = 0
    for i in range(len(name)):
        sheet.write(row, i, name[i])
    row = row + 1
    outfile.save("./微博数据0317.xls")


# 将dic中的内容写入excel
def writeXLS(dic):
    global row
    global outfile
    global sheet

    for k in dic:
        for i in range(len(dic[k])):
            sheet.write(row, i, dic[k][i])
        row = row + 1
    outfile.save("./微博数据0317.xls")


# 在页面有内容的前提下，获取内容
def getContent():
    # 寻找到每一条微博的class
    try:
        nodes = driver.find_elements_by_xpath("//div[@class='card-wrap']/div[@class='card']")
    except Exception as e:
        print(e)

    # 在运行过程中微博数==0的情况，可能是微博反爬机制，需要输入验证码
    if len(nodes) == 0:
        input("请在微博页面输入验证码！")
        url = driver.current_url
        driver.get(url)
        getContent()
        return

    dic = {}

    global page
    print(start_stamp.strftime("%Y-%m-%d-%H"))
    print('页数:', page)
    page = page + 1
    print('微博数量', len(nodes))

    for i in range(len(nodes)):
        dic[i] = []
        try:
            BZNC = nodes[i].find_element_by_xpath(".//div[@class='content']/p[@class='txt']").get_attribute("nick-name")
        except:
            BZNC = ''
        print('博主昵称:', BZNC)
        dic[i].append(BZNC)

        try:
            #WBRZ = nodes[i].find_element_by_xpath(".//div[@class='info']/div/a[contains(@title,'微博')]").get_attribute('title') # 若没有认证则不存在节点
            WBRZ = nodes[i].find_element_by_xpath(".//div[@class='avator']/a/span[@class = 'woo-icon-wrap woo-avatar-icon']").get_attribute(
                'title')  # 若没有认证则不存在节点
        except:
            WBRZ = ''
        print('微博认证:', WBRZ)
        dic[i].append(WBRZ)
        # 判断展开全文和网页链接是否存在
        try:
            nodes[i].find_element_by_xpath(".//div[@class='content']/p[@class='txt']/a[@action-type='fl_unfold']").is_displayed()
            flag = True
        except:
            flag = False
        # 获取微博内容
        try:
            if flag:
                nodes[i].find_element_by_xpath(".//div[@class='content']/p[@class='txt']/a[@action-type='fl_unfold']").click()
                time.sleep(1)
                # WBNR = nodes[i].find_element_by_xpath(".//div[@class='content']/p[2]").text.replace("\n","")
                WBNR = nodes[i].find_element_by_xpath(".//div[@class='content']/p[@node-type='feed_list_content_full']").text.replace("\n","")
                # 判断发布位置是否存在
                try:
                    nodes[i].find_element_by_xpath(".//div[@class='content']/p[@class='txt']/a/i[@class='wbicon']").is_displayed()
                    flag = True
                except:
                    flag = False
                # 获取微博发布位置
                try:
                    if flag:
                        pattern = nodes[i].find_elements_by_xpath(".//div[@class='content']/p[2]/a[i[@class='wbicon']]")
                        if isinstance(pattern,list):
                            text = [p.text for p in pattern]
                            FBWZ = [loc for loc in [re.findall('^2(.*$)', t) for t in text] if len(loc) > 0][0][0]
                        else:
                            text = pattern.text
                            FBWZ = re.findall('^2(.*$)',text)[0]
                    else:
                        FBWZ = ''
                except:
                    FBWZ = ''
            else:
                WBNR = nodes[i].find_element_by_xpath(".//div[@class='content']/p[@class='txt']").text.replace("\n","")
                # 判断发布位置是否存在
                try:
                    nodes[i].find_element_by_xpath(".//div[@class='content']/p[@class='txt']/a/i[@class='wbicon']").is_displayed()
                    flag = True
                except:
                    flag = False
                # 获取微博发布位置
                try:
                    if flag:
                        pattern = nodes[i].find_elements_by_xpath(".//div[@class='content']/p[@class='txt']/a[i[@class='wbicon']]")
                        if isinstance(pattern,list):
                            text = [p.text for p in pattern]
                            FBWZ = [loc for loc in [re.findall('^2(.*$)', t) for t in text] if len(loc) > 0][0][0]
                        else:
                            text = pattern.text
                            FBWZ = re.findall('^2(.*$)',text)[0]
                    else:
                        FBWZ = ''
                except:
                    FBWZ = ''
        except:
            WBNR = ''
        print('微博内容:', WBNR[:5])
        dic[i].append(WBNR)

        # print('发布位置:', FBWZ)
        # dic[i].append(FBWZ)

        try:
            FBSJ = nodes[i].find_element_by_xpath(".//div[@class='content']/p[@class='from']/a[1]").text
        except:
            FBSJ = ''
        print('发布时间:', FBSJ)
        dic[i].append(FBSJ)

        try:
            ZF_TEXT = nodes[i].find_element_by_xpath(".//a[@action-type='feed_list_forward']").text
            # ZF_TEXT = nodes[i].find_element_by_xpath(".//div[@class='content']").text
            if ZF_TEXT == '转发':
                ZF = 0
            else:
                ZF = int(ZF_TEXT.split(' ')[0])
        except:
            ZF = 0
        print('转发:', ZF)
        dic[i].append(ZF)
        # print('\n')

        try:
            PL_TEXT = nodes[i].find_element_by_xpath(".//a[@action-type='feed_list_comment']").text
            # ZF_TEXT = nodes[i].find_element_by_xpath(".//div[@class='content']").text
            if PL_TEXT == '评论':
                PL = 0
            else:
                PL = int(PL_TEXT.split(' ')[0])
        except:
            PL = 0
        print('评论:', PL)
        dic[i].append(PL)
        # print('\n')

        try:
            Z_TEXT = nodes[i].find_element_by_xpath(".//span[@class='woo-like-count']").text
            # ZF_TEXT = nodes[i].find_element_by_xpath(".//div[@class='content']").text
            if Z_TEXT == '赞':
                Z = 0
            else:
                Z = int(Z_TEXT.split(' ')[0])
        except:
            Z = 0
        print('赞:', Z)
        dic[i].append(Z)
        print('\n')

    # 写入Excel
    writeXLS(dic)


# *******************************************************************************
#                                程序入口
# *******************************************************************************
if __name__ == '__main__':
    # 定义变量
    username = '18603899634'  # 输入你的用户名
    password = 'qq529106896'  # 输入你的密码

    # 操作函数
    LoginWeibo(username, password)  # 登陆微博
    key = '元宇宙'
    GetSearchContent(key)
