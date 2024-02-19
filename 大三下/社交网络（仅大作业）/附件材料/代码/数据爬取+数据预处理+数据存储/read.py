import os
import pandas as pd
import warnings
from tqdm import tqdm

warnings.filterwarnings('ignore')

raw_dataframe = pd.DataFrame()

def walk_dir(dir_path):
    for curr, dirs, files in os.walk(dir_path):
        for file in files:
            if not file.endswith(".xlsx"):
                continue
            fpath = os.path.join(curr, file)
            update_file(fpath)

def update_file(file_path):
    global raw_dataframe
    print("\ncurrent file：", file_path)
    excel_file = pd.ExcelFile(file_path)
    sheet_name = excel_file.sheet_names
    for i in tqdm(sheet_name):
        df_tmp = pd.read_excel(file_path, sheet_name=i)
        if raw_dataframe.empty:
            raw_dataframe = df_tmp
        else:
            raw_dataframe = pd.concat([raw_dataframe, df_tmp], axis=0, ignore_index=True)
    print("file %s read completed" % file_path)

# 数据预处理
def preHandle(df):
    df['微博内容'] = df['微博内容'].str.replace(r'[^\w]+', '')
    df.drop_duplicates(['微博内容'], keep='last', inplace=True)
    df.reset_index(drop=True, inplace=True)

if __name__ == '__main__':
    walk_dir("data")
    print("ready to preprocess")
    print(raw_dataframe.head())
    preHandle(raw_dataframe)
    print("preprocess complete")
    print(raw_dataframe.head())
    # raw_dataframe.rename(columns={'博主昵称': 'weibo_username', '微博认证': 'weibo_verification', '微博内容': 'weibo_content', '发布时间': 'submit_time', '转发': 'forward_counts', '评论': 'comments_counts', '赞': 'points_times'}, inplace=True)
    # # print(raw_dataframe.head())
    # raw_dataframe.to_csv("weibo_data_utf8.csv", index=0, encoding='utf-8')
    # print("export successfully")