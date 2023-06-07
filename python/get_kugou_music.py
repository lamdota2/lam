import requests
#import time
#import math
import re
import os
import json
from bs4 import  BeautifulSoup

header={
    'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36'
}

def get_music(hash_data,album):
    url = 'https://wwwapi.kugou.com/yy/index.php?'
    print('start get_music')
    data = {
        'r': 'play/getdata',
        #'callback': 'jQuery19108922952455208721_{}'.format(math.floor(time.time()*1000)),
        'hash': 'hash_data',
        'album_id': album
        #  'hash': '0C117B96110D71F00BEF6BD68F4FE88B',
        #  'album_id': '48738309'
    }

    dic_headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36',
        'cookie': 'kg_mid=e9f7036c9e3f7b3b8e5f31d8c437a650; kg_dfid=1aF1fa3fRahL0i1GZz3RYp8h; _WCMID=1648cadf5e0f206e4bca9435; kg_dfid_collect=d41d8cd98f00b204e9800998ecf8427e; Hm_lvt_aedee6983d4cfc62f509129360d6bb3d=1584362882; Hm_lpvt_aedee6983d4cfc62f509129360d6bb3d=1584362905; kg_mid_temp=e9f7036c9e3f7b3b8e5f31d8c437a650',
        'Referer': 'https://www.kugou.com/yy/rank/home/1-6666.html?from=rank'
    }
    print(hash_data,album)
    url_1 = f'https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash={hash_data}&album_id={album}'
    print(url_1)
    html = requests.get(url_1, headers = dic_headers)
    print(html.text)

    # start = html.text.index('{')
    # end = html.text.index('})')+1
    # if start_index != -1 and end_index != 0:
    #     start = start_index
    #     end = end_index
    # else:
    #     # Handle the case when the substrings are not found
    #     print("Substring not found in html.text")
    json_data = json.loads(html.text)
    
    song_name = json_data['data']['song_name']
    song_author = json_data['data']['author_name']
    song_url = json_data['data']['play_url']
    name = song_name+ '-'+ song_author

    print(song_url)
    print(name)
    download_music(song_url,name)


def download_music(url,name):
    if url =="":
        print('url is null')
    else:
        print('正在下载音乐......')
        with open(f'{name}.mp3','wb') as f:
            f.write(requests.get(url).content)
        print('音乐下载完毕')


def get_hash_data():
    url = 'https://www.kugou.com/yy/special/single/547134.html'
    html = requests.get(url)
    soup = BeautifulSoup(html.text,'lxml')
    hash_datas_a = soup.select('#songs li a')
    for hash_data_a in hash_datas_a[:5]:
        hash_data = hash_data_a['data'].split('|')[0]
        print(hash_data)
        get_music(hash_data)

#get_hash_data()

def get_hash_data1():
    url = 'https://www.kugou.com/yy/rank/home/1-23784.html?from=rank'
    #url = 'https://www.kugou.com/yy/html/rank.html'
    html = requests.get(url,headers=header)
    #print(html.text)
    hash_data_lst = re.findall(r'{"Hash":"(.*?)"', html.text)
    album_id_list = re.findall('"album_id":(\d+),',html.text)
    for hash, album  in zip(hash_data_lst[:3],album_id_list[:3]):
        print(hash,album)
        get_music(hash,album)

get_hash_data1()
