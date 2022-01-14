# E16DST1
・e16evb02、ccjbox6でcompileできることを確認済みです。

・CmakeLists.txtに二か所、include/E16DST_DST1DefaultFilePath.hh.inに一か所evb<->ccjで選択が必要な行があるので、それぞれで使うときは確認してください。

・src/E16DST_DST1xxxHitAndCluster.cc内に

　int E16DST_DST1xxxHitAndCluster()と

　E16DST_DST1xxxHit (とCluster) ::LocalPos(), GlobalPos()

　を実装してください。

・geometryはE16ANA_GeometryV2の定義に従ってください。

・まだ途中なので.dst1は生成できません。適宜更新していきます。

・dst0のsampleは例えば

　evb02:/e16/w/data102z/trg/junkdata/dst0_ccj

　にあります。
 
・CalibDBの基本的な運用方針 (うまくいかない場合はとりあえず従わなくてよい)

　CalibDBManager、Calibxxxyyy (各検出器のDB class) はmainで呼び、runが変わるたびにManagerと各検出器のclassにsetする。

　Factory(E16ANA_Calibxxxyyy& xxx_yyy)などのように各検出器classを参照渡しする。

・プログラムのチェックはdst0_to_dst1.ccではなくdst0_to_dst1_xxx_check.ccを使ってください。

　それ以外の書き換えであればdst0_to_dst1.ccを編集して構いません。他のdst0_to_dst1_xxx_check.ccを編集はしなくて大丈夫です。

・run0b (DST0 Version4) について解析する場合は、

　$ cd E16DST
 
　$ git checkout 094ffb8
 
　としてversion4のE16DSTをとってきてください。
