# dearoot
项目描述见 [语雀链接](https://www.yuque.com/docs/share/be539e92-a58e-4d8d-8590-99755eb216aa?#%20%E3%80%8A%E8%87%B4%E4%BA%B2%E7%88%B1%E7%9A%84root%E3%80%8B)

20221113，修复khook的sys_write函数中tmp没有free从而在卸载模块时卡住的bug

20221023，修改了ss下隐藏端口的bug，提升了该功能的兼容性，现在兼容3、4、5系列内核，2系列内核未测试，可能不能在2.6.33以下的版本正常工作
