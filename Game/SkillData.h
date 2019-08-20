#pragma once

const int SkillKazu = 24; //スキル数

const struct _Skill { //スキルデータ用構造体
	wchar_t SkillName[128]; //スキル名
	wchar_t SkillHint[255]; //未入手時のヒント
	wchar_t SkillSetumei[255]; //スキル説明
	int StarPower; //消費流星ゲージ 0の場合パッシブスキルとして扱う
	wchar_t SkillIcon[255]; //スキル画像
	wchar_t SkillTran[255]; //トランシーバーのセリフ

};

const struct _Skill Skill_Data[SkillKazu]{ //スキルデータ
	{ L"りゅうせいダッシュ" , L"さいしょから もっている", L"てきを かんつうする\nとっしんをくりだす" , 100 , L"sprite/skillicon_1.dds",L"イノチガケ ノ\nトッシン コウゲキ デス" },
	{ L"こんぺいとうダッシュ" , L"シーソークスを たおそう", L"てきを かんつうする\nとっしんをくりだす" , 50 , L"sprite/skillicon_2.dds",L"リュウセイダッシュ ヨリ\nコンパクトナ タイプデス" },
	{ L"すいせいダッシュ", L"STAGE1のHARDで\nSランクを かくとくしよう" , L"スライドパッドでほうこうを\nちょうせい できるぞ" , 100 , L"sprite/skillicon_3.dds",L"ソウサカノウ ナ\nリュウセイダッシュ\nデスネ" },
	{ L"スタードロップ" , L"キコウチュウマークを\n1つ あつめよう", L"はつどうすると ほしが\n1こ でてくる" , 50 , L"sprite/skillicon_4.dds",L"ガメンヲ スコシ\nアカルク デキマス" },
	{ L"カガヤキノウミ" , L"キコウチュウマークを\n3つ あつめよう", L"はつどうちゅうは まわりが\nとてもあかるくなる" , 75 , L"sprite/skillicon_5.dds",L"シバラク トテモ\nアカルク ナリマスヨ" },
	{ L"スターフィーバー" , L"キコウチュウマークを\n5つ あつめよう", L"はつどうすると ほしが\n3こ でてくる" , 100 , L"sprite/skillicon_6.dds" ,L"ガメンヲ ソレナリニ\nアカルク デキマス" },
	{ L"ミルキーウェイ" , L"キコウチュウマークを\nぜんぶ あつめよう", L"はつどうすると ほしが\n10こ でてくる" , 100 , L"sprite/skillicon_7.dds",L"ガメンヲ トテモ\nアカルク デキマス" },
	{ L"ゾンビタイム" , L"STAGE4で\nアイテムを 15こひろおう", L"はつどうちゅうは てきを\nたおしても しなない" , 100 , L"sprite/skillicon_8.dds",L"テキノ コウゲキハ\nムコウカ デキマセンヨ" },
	{ L"ナガレボシ" , L"STAGE2で\nSランクを かくとくしよう", L"はつどうちゅうは\nいどうそくど アップ！" , 75 , L"sprite/skillicon_9.dds",L"シバラク トテモ\nウゴキヤスク ナリマス" },
	{ L"ソウルフレア" , L"STAGE2でばくだんに\nあたらずクリアしよう", L"しばらくチャージして\nだいばくはつ する" , 100 , L"sprite/skillicon_10.dds",L"シュウイノ テキヲ\nイッキニ タオセマス" },
	{ L"コメットキャノン" , L"STAGE3ででんしゃに\nひかれずクリアしよう", L"はつどうちゅうは\nいんせきをはっしゃできる" , 100 , L"sprite/skillicon_11.dds",L"セッテイシタ スキルノ\nボタンデ インセキヲ\nトバシマス" },
	{ L"せいめいりょく" , L"STAGE3のHARDで\nSランクを かくとくしよう", L"しようすると ざんきが\nすこしだけふえる" , 100 , L"sprite/skillicon_12.dds" ,L"イノチヲ フヤスナンテ\nズルクナイデスカ" },
	{ L"アタックアップ" , L"てきをるいけい\n10たい たおそう", L"こうげきりょくが あがる" , 0 , L"sprite/skillicon_13.dds",L"イツデモ\nコウゲキリョク\n1.2バイ デス！" },
	{ L"ムテキノバシ" , L"てきをるいけい\n30たい たおそう", L"むてきじかんが\nながくなる" , 0 , L"sprite/skillicon_14.dds" ,L"ムテキジカン ガ\n2バイ ニナリマス" },
	{ L"アイテムブースト" , L"てきをるいけい\n50たい たおそう", L"アイテムをひろったときの\nゲージじょうしょうりょう+" , 0 , L"sprite/skillicon_15.dds",L"スキルヲ タクサン\nツカイタイ アナタニ\nオススメデス" },
	{ L"セツヤク" , L"てきをるいけい\n70たい たおそう", L"ダッシュをしたときの\nじゅみょうげんしょう1/2" , 0 , L"sprite/skillicon_16.dds",L"ハヤク ハヤク\nハシリタイ アナタニ\nオススメデス" },
	{ L"イノチカンゲン" , L"てきをるいけい\n100たい たおそう", L"ダッシュをするだけで\nゲージがすこしふえる" , 0 , L"sprite/skillicon_17.dds",L"ホントウニ スコシデスガ\nオトク デスヨネ" },
	{ L"ハガネノカラダ" , L"てきをるいけい\n150たい たおそう", L"てきのたまに あたっても\nしななくなる" , 0 , L"sprite/skillicon_18.dds" ,L"カワリニ ジュミョウ ガ\nスコシ ヘリマスガ..." },
	{ L"カミカゼバトル" , L"りゅうせいダッシュで\nボスにトドメを5かいさそう", L"じゅみょうが はやくへるが\nこうげきといどうそくど+" , 0 , L"sprite/skillicon_19.dds",L"ギリギリノ バトルヲ\nタノシミタイ アナタニ\nオススメデス" },
	{ L"アクム" , L"ハードモードを1かい\nクリアしよう", L"いどうそくどがさがるが\nかくとくスコア1.5ばい" , 0 , L"sprite/skillicon_20.dds",L"ダッシュデ イドウ\nスルノガ ダイジデス" },
	{ L"キョウフ" , L"ハードモードを3かい\nクリアしよう", L"ゲージがかってにふえない\nかくとくスコア1.5ばい" , 0 , L"sprite/skillicon_21.dds",L"アイテムヲ タクサン\nアツメナクテハ..." },
	{ L"ナミダ" , L"ハードモードを5かい\nクリアしよう", L"ほし がでないが\nかくとくスコア2.0ばい" , 0 , L"sprite/skillicon_22.dds",L"クライ クライ\nヤミノ セカイデス" },
	{ L"キコサーチ" , L"STAGE5のHARDで\nSランクを かくとくしよう", L"キコウチュウが\nレーダーにうつる" , 50 , L"sprite/skillicon_23.dds",L"アノムシヲ\nミツケタイ アナタニ\nオススメデス" },
	{ L"アイテムレーダー" , L"???????", L"アイテムがつねに\nレーダーにうつる" , 0 , L"sprite/skillicon_24.dds",L"コレデ スキルガ\nダシホウダイ！\n...デスカネ？" },

};