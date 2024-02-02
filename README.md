# dearoot
项目描述见 [语雀链接](https://www.yuque.com/docs/share/be539e92-a58e-4d8d-8590-99755eb216aa?#%20%E3%80%8A%E8%87%B4%E4%BA%B2%E7%88%B1%E7%9A%84root%E3%80%8B)

20221113，修复khook的sys_write函数中tmp没有free从而在卸载模块时卡住的bug。注：除此之外，还有文件内容隐藏模块原先就存在bug，在某些系统例如ubuntu16下，若启用了文件内容隐藏功能，卸载时也会卡住，如果有卸载模块的需求请谨慎启用这个功能

20221023，修改了ss下隐藏端口的bug，提升了该功能的兼容性，现在兼容3、4、5系列（5.7以前的）内核，2系列内核未测试，可能不能在2.6.33以下的版本正常工作。对于Linux内核5.7以上版本，目前暂不支持，5.7版本后安全起见移出了khook模块依赖的kallsyms_lookup_name()和kallsyms_on_each_symbol()。
