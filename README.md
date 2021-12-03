# Novel_Engine
ノベルゲームのエンジン　DXライブラリで製作中  
現在アルファ版

## 概要
### このソフトについて
[DXライブラリ](https://dxlib.xsrv.jp/)で製作中の、ノベルゲームのエンジンみたいなものです。現在はソースコードのみの公開となっています。  
なお、Windows専用となっています。

### 現在アルファ版
現在アルファ版です。正式版ではないため、不完全だったり、仕様があれこれ変更になったりといった可能性大です。例えば、ノベルゲームには必須の立ち絵表示機能の実装はこれから行う予定です（README書いている場合じゃないですね......）。

### 動作環境
「古すぎない普通のWindowsパソコン」で動きます。  
具体的には、DXライブラリの動作環境
 - WindowsXP以上のOSがインストールされたパソコン
 - DirectX9以降がインストールされていること（通常のPCであれば、購入時点でインストールされているので、心配はないと思います）

で動きます。

### 本ソフトの特徴（実装予定含む）

 - ノベルゲーム制作に特化
 - テキスト表示など、基本的なノベルゲームの機能は搭載済み（プログラミング不要）
 - JSONファイルでセリフの記述や背景画像の指定などができる（JSONファイルは、プログラミング未経験者でもすぐに扱えるようになるテキストファイルのようなものです）
 - C++言語で書かれたソースコードを改造することで、オリジナルの機能を追加できる（かなり上級者向け？）
 
ノベルゲームに必要不可欠な機能の実装を目指していますが、派手な演出や細かいギミックなどまでは手が回らない気がしています。残念ですが、それらをお求めの方にはお応えできません。

以下、仕様などを説明予定


## 使用ライブラリ
本ソフトは以下のライブラリを使わせていただいています。  
また、本ソフト配布時には、説明書などにこれらと同じ内容を記載していただきますよう、お願い申し上げます。
<ul>
    <li><a href="https://dxlib.xsrv.jp/">DXライブラリ</a>：Ver 3.23（ソースコードには含まれていません）<br/><details><summary>著作権表示</summary><div>
libjpeg　Copyright (C) 1991-2013, Thomas G. Lane, Guido Vollbeding.<br/>
this software is based in part on the work of the Independent JPEG Group
<br/><br/><br/>
libpng　Copyright (C) 2004, 2006-2012 Glenn Randers-Pehrson.<br/>
zlib　Copyright (C) 1995-2012 Jean-loup Gailly and Mark Adler.
<br/><br/><br/>
libtiff　Copyright (c) 1988-1997 Sam Leffler<br/>
libtiff　Copyright (c) 1991-1997 Silicon Graphics, Inc.
<br/><br/>
Permission to use, copy, modify, distribute, and sell this software and
its documentation for any purpose is hereby granted without fee, provided
that (i) the above copyright notices and this permission notice appear in
all copies of the software and related documentation, and (ii) the names of
Sam Leffler and Silicon Graphics may not be used in any advertising or
publicity relating to the software without the specific, prior written
permission of Sam Leffler and Silicon Graphics.
<br/><br/>
THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
<br/><br/>
IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.
<br/><br/><br/>
libogg　Copyright (C) 2002-2009 Xiph.org Foundation
<br/><br/>
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
<br/><br/>
- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
<br/><br/>
- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
<br/><br/>
- Neither the name of the Xiph.org Foundation nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.
<br/><br/>
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
<br/><br/><br/>
Opus audio codec<br/>
Copyright 2001-2011 Xiph.Org, Skype Limited, Octasic,
Jean-Marc Valin, Timothy B. Terriberry,
CSIRO, Gregory Maxwell, Mark Borgerding,
Erik de Castro Lopo
<br/><br/>
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
<br/><br/>
- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
<br/><br/>
- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
<br/><br/>
- Neither the name of Internet Society, IETF or IETF Trust, nor the
names of specific contributors, may be used to endorse or promote
products derived from this software without specific prior written
permission.
<br/><br/>
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
<br/><br/><br/>
Opusfile<br/>
Copyright (c) 1994-2013 Xiph.Org Foundation and contributors
<br/><br/>
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
<br/><br/>
- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
<br/><br/>
- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
<br/><br/>
- Neither the name of the Xiph.Org Foundation nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.
<br/><br/>
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
<br/><br/><br/>
Mersenne Twister<br/>
Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.
<br/><br/>
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
<br/><br/>
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
<br/><br/>
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
<br/><br/>
3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.
<br/><br/>
THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
<br/><br/><br/>
Bullet　Copyright (c) 2003-2006 Erwin Coumans.
<br/><br/>
    </div></details></li>
    <li><a href="https://github.com/nlohmann/json">nlohmann/json</a>：version 3.10.4<br/><details><summary>著作権表示</summary><div>
Copyright (c) 2013-2021 Niels Lohmann
<br/><br/>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
<br/><br/>
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
<br/><br/>
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
<br/><br/>
    </div></details></li>
    <li><a href="https://github.com/javacommons/strconv">javacommons/strconv</a>：v1.8.10<br/><details><summary>著作権表示</summary><div>
Copyright (c) 2019-2021 JavaCommons
<br/><br/>
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
<br/><br/>
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
<br/><br/>
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
<br/><br/>
    </div></summary></li>
</ul>

