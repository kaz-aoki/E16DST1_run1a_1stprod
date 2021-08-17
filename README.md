# E16DST1
・e16evb02、ccjbox6でcompileできることを確認済みです。

・src/E16DST_DST1xxxHitAndCluster.cc内に

　int E16DST_DST1xxxHitAndCluster()と

　E16DST_DST1xxxHit (とCluster) ::LocalPos(), GlobalPos()

　を実装してください。

・もう少し詳しいことはindicoの"analysis_meeting/2021.08.04/trigger"のスライドを見てください。

・まだ途中なので.dst1は生成できません。適宜更新していきます。

・E16ANA_Geometryを使いたい場合は

　ccj: cp -r /ccj/w/data06a/E16/user/ozawa/sw/geant4.10.07_install/include ${E16DST1}/E16ANA_Geometry/include/geant4

　evb: cp -r /e16/u/ichikawa/work/dst1/E16DST1/E16ANA_Geometry/include/geant4 ${E16DST1}/E16ANA_Geometry/include/

　などとしてください。

・dst0のsampleは例えば

　evb02:/e16/w/data102z/trg/junkdata/dst0merge/run030778_sink0_000_srs_trg_lg_ssd.dst0

　にあります。
