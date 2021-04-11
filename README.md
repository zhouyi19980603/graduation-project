# graduation-project
毕业设计——FreeC即时通讯系统

4-11 修复了聊天中存储记录的问题，并实现离线状态聊天
fix说明，
fix-1: 消息记录保存json格式，
chatHistory.json
id,msg_type,msg_content,send_id,recv_id,time
{
"id": {"id":"","msg_type":""},
"历史记录的id": {}
}

userChatHistory.json
{
    "用户id",["历史记录的id",""],
    "用户id2",["历史记录id1","历史记录id2"]
}

当初始化登录用户的聊天记录时就从里面获取，先查询usrChatHistory.josn在根据历史记录的id进行查询

当有消息来时，会把消息的id进行保存，同时要写入json文件中去，用户登录初始化时从文件中去读取并发送过去

fix-2: 修复单聊支持离线聊天的功能
