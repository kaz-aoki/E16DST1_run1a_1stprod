# E16DST1
・まだ途中なので.dst1は生成できません。適宜更新していきます。
 
・CalibDBの基本的な運用方針 (うまくいかない場合はとりあえず従わなくてよい)

　CalibDBManager、Calibxxxyyy (各検出器のDB class) はmainで呼び、runが変わるたびにManagerと各検出器のclassにsetする。

　Factory(E16ANA_Calibxxxyyy& xxx_yyy)などのように各検出器classを参照渡しする。

・プログラムのチェックはdst0_to_dst1.ccではなくdst0_to_dst1_xxx_check.ccを使ってください。

　それ以外の書き換えであればdst0_to_dst1.ccを編集して構いません。他のdst0_to_dst1_xxx_check.ccを編集はしなくて大丈夫です。

・run0b (DST0 Version4) について解析する場合は、

　$ cd E16DST
 
　$ git checkout 094ffb8
 
　としてversion4のE16DSTをとってきてください。



