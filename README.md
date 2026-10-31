# rockbox-ipodvideo

Rockbox の個人用カスタムフォーク。主に iPod Video（5/5.5世代）向けにビルドして使う。
2011年頃に使っていた自前パッチ一式を、現在の上流（Rockbox/rockbox）に合わせて移植したもの。
カスタマイズは `ipodvideo-custom` ブランチに入っている。

## 適用しているパッチ

| # | 内容 | コミット | 対象範囲 |
|---|------|---------|---------|
| 1 | ボタンのリピート開始を 300ms → 600ms（元パッチ 00） | [`da0ed4835`](https://github.com/maganori/rockbox-ipodvideo/commit/da0ed483555986e0cc663fc34a36152d05cdb3f8) | 全ターゲット共通 |
| 2 | dircache 拡大（予約 64KB→256KB、上限 6MB→12MB）。ファイル数の多い大容量ライブラリ向け（元パッチ 01） | [`b5f6148a9`](https://github.com/maganori/rockbox-ipodvideo/commit/b5f6148a9eebebe0cacdee1b8b57d2fec9d316e0) | 全ターゲット共通 |
| 3 | 「ホールドスイッチで電源オフ」設定を追加（充電中は発動しない）（元パッチ 12） | [`3397517ad`](https://github.com/maganori/rockbox-ipodvideo/commit/3397517ad54e1cd949720e6b92a26c9b9e79a09f) | 全ターゲット共通 |
| 4 | アラームの残差分（2分未満でも設定可、表示を設定時刻に）（元パッチ 11） | [`49ec24f55`](https://github.com/maganori/rockbox-ipodvideo/commit/49ec24f553893c6e9c2366b6da0ae6a7cd272639) | 全ターゲット共通 |
| 5 | PP502x QuickBoost（CPU 周波数切替を PLL_CONTROL 変更のみに高速化）（元パッチ 14） | [`032d7b68f`](https://github.com/maganori/rockbox-ipodvideo/commit/032d7b68f9a71cd3edc083cdf08e60a1e659e251) | PP502x 系全体（iPod 4G/Photo/mini/nano 1G 等にも効く） |
| 6 | フォントバッファ上限を 2MB に（MEMORYSIZE>4 の場合）（元パッチ 02） | [`8d86e3bf8`](https://github.com/maganori/rockbox-ipodvideo/commit/8d86e3bf86d99d1ad832e1c1ef5cd2d3613ac190) | 全ターゲット共通 |
| 7 | UI フォント 15/19 を日本語フォント（SHG30P）に差し替え | [`ab4847a31`](https://github.com/maganori/rockbox-ipodvideo/commit/ab4847a31898a320851bc1326d389e3ffbeec794) | fonts/ 共通資産 |
| 8 | システムフォント変換の MAXCHAR を 255 → 65535（元パッチ 10） | [`8a0dadf6e`](https://github.com/maganori/rockbox-ipodvideo/commit/8a0dadf6e15194d4524b9ce3d44966f5a5ace790) | 全ターゲット共通（ビルド時） |
| 9 | システムフォントに日本語フォント（rockbox_default）を採用 | [`c665fbf81`](https://github.com/maganori/rockbox-ipodvideo/commit/c665fbf813c9c197209df53237f248920e572e58) | ipodvideo 向けビルドのみ |
| 10 | 起動ロゴの表示位置を全画面に（y=10→0）（元パッチ 04） | [`85f3b242a`](https://github.com/maganori/rockbox-ipodvideo/commit/85f3b242a65c173ab8017fcc3c01132047dc81b5) | 全ターゲット共通 |
| 11 | 起動ロゴを 320×240 のカスタム画像に差し替え | [`f8a7ca4d8`](https://github.com/maganori/rockbox-ipodvideo/commit/f8a7ca4d85f37089e65a30505758d0b769326e73) | 320×240 画面向け |
| 12 | シミュレータの充電シミュレーション高速化＋ charge_state 遷移（元パッチ 13） | [`8aeba4787`](https://github.com/maganori/rockbox-ipodvideo/commit/8aeba4787031dd85ffa30f883d7840736dca24b8) | シミュレータ専用 |
| 13 | シミュレータのイベント待ちを Windows ではポーリング方式に変更（SDL_WaitEvent が即時失敗する環境で起動直後に終了するため。Windows 以外は従来通り） | [f4f805066](https://github.com/maganori/rockbox-ipodvideo/commit/f4f80506662dd13a289126e7b685628fcfb59480) |

## iFlash 等のストレージ換装について

- このフォークには、iFlash をはじめとする SD/CF アダプタ向けの互換性対策は**入っていない**。大容量ドライブやアダプタの動作は上流 Rockbox の対応範囲に依存する
- 大容量化でファイル数が増えた場合に効く変更として、dircache の上限拡大（#2）は入っている
- 動作確認は純正 HDD（80GB）環境でのみ行っている
