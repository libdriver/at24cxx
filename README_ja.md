[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AT24CXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/at24cxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AT24CXXは、Microchip社が発売したIICバスのEEPROMです。 1.7v〜5.5vの電源範囲、IIC標準モード（100kHz）、高速モード（400kHz）、高速モード（1MHz）をサポートします。

LibDriver AT24CXXは、LibDriverによって起動されたAT24CXXの全機能ドライバーです。 AT24CXXは、EEPROMの書き込みおよび読み取り機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver AT24CXXのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver AT24CXX用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver AT24CXXドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver AT24CXXプログラミング例が含まれています。

/ docディレクトリには、LibDriver AT24CXXオフラインドキュメントが含まれています。

/ datasheetディレクトリには、AT24CXXデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_at24cxx_basic.h"

uint8_t res;
uint8_t data;

res = at24cxx_basic_init(AT24C01, AT24CXX_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...

res = at24cxx_basic_read(0x00, (uint8_t *)&data, 1);
if (res != 0)
{
    (void)at24cxx_basic_deinit();

    return 1;
}
else
{
    at24cxx_interface_debug_print("at24cxx: 0x%02X.\n", data);
}

...

res = at24cxx_basic_write(0x00, (uint8_t *)&data, 1);
if (res != 0)
{
    (void)at24cxx_basic_deinit();

    return 1;
}
else
{
    at24cxx_interface_debug_print("at24cxx: 0x%02X.\n", data);
}

...

(void)at24cxx_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/at24cxx/index.html](https://www.libdriver.com/docs/at24cxx/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。