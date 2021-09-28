# E16DST1
・e16evb02、ccjbox6でcompileできることを確認済みです。

・src/E16DST_DST1xxxHitAndCluster.cc内に

　int E16DST_DST1xxxHitAndCluster()と

　E16DST_DST1xxxHit (とCluster) ::LocalPos(), GlobalPos()

　を実装してください。

・もう少し詳しいことはindicoの"analysis_meeting/2021.08.04/trigger"のスライドを見てください。

　-> geometryはE16ANA_GeometryV2の定義に従ってください。

・まだ途中なので.dst1は生成できません。適宜更新していきます。

・dst0のsampleは例えば

　evb02:/e16/w/data102z/trg/junkdata/dst0merge/run030778_sink0_000_srs_trg_lg_ssd.dst0

　にあります。
 
・CalibDBの基本的な運用方針 (うまくいかない場合はとりあえず従わなくてよい)

　CalibDBManager、Calibxxxyyy (各検出器のDB class) はmainで呼び、runが変わるたびにManagerと各検出器のclassにsetする。

　Factory(E16ANA_Calibxxxyyy& xxx_yyy)などのように各検出器classを参照渡しする。

・プログラムのチェックはdst0_to_dst1.ccではなくdst0_to_dst1_xxx_check.ccを使ってください。

　それ以外の書き換えであればdst0_to_dst1.ccを編集して構いません。他のdst0_to_dst1_xxx_check.ccを編集はしなくて大丈夫です。
