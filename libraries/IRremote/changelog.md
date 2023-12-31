# Changelog
The latest version may not be released!
See also the commit log at github: https://github.com/Arduino-IRremote/Arduino-IRremote/commits/master

## 3.5.2
- Improved support for Teensy boards by Paul Stoffregen.

## 3.5.1
- Renamed INFO_PRINT to IR_INFO_PRINT as well as for DEBUG and TRACE.
- Fixed error with DEBUG in TinyIRReceiver.hpp.
- Support for ATmega88 see issue #923. Thanks to Dolmant.
- NO_LED_FEEDBACK_CODE replaces and extends DISABLE_LED_FEEDBACK_FOR_RECEIVE.
- Removed NO_LEGACY_COMPATIBILITY macro, it was useless now.
- Fix ESP32 send bug see issue #927.

## 3.5.0
- Improved ir_DistanceProtocol.
- Tone for ESP32.
- last phase renamed *.cpp.h to .hpp.
- No deprecation print for ATtinies.
- Renamed ac_LG.cpp to ac_LG.hpp.
- Maintained MagiQuest by E. Stuart Hicks.
- Improved print Pronto by Asuki Kono.
- Added printActiveIRProtocols() function.
- Used IR_SEND_PIN to reduce code size and improved send timing for AVR.

## 3.4.0
- Added LG2 protocol.
- Added ATtiny167 (Digispark Pro) support.
- Renamed *.cpp.h to .hpp.
- organized carrier frequencies.
- Compiler switch USE_OPEN_DRAIN_OUTPUT_FOR_SEND_PIN added.
- Moved blink13() back to IRrecv class.
- Added Kaseikyo convenience functions like sendKaseikyo_Denon().
- Improved / adjusted LG protocol and added class Aircondition_LG based on real hardware supplied by makerspace 201 (https://wiki.hackerspaces.org/ZwoNullEins) from Cologne.
- Improved universal decoder for pulse width or pulse distance protocols to support more than 32 bits.
- Added mbed support.

## 3.3.0
- Fix errors if LED_BUILTIN is not defined.
- Fixed error for AVR timer1. Thanks to alexbarcelo.
- New example IRremoteExtensionTest.
- Enabled megaAVR 0-series devices.
- Added universal decoder for pulse width or pulse distance protocols.

## 3.2.0
- Fix for ESP32 send Error, removed `USE_SOFT_SEND_PWM` macro.
- Added Onkyo protocol.
- Support for old 2.x code by backwards compatible `decode(decode_results *aResults)` function.
- Removed USE_OLD_DECODE macro and added NO_LEGACY_COMPATIBILITY macro.
- Added ATtiny1604 support.
- New SendAndReceive example.
- Added ESP8266 support.
- Extended DEBUG output.

## 3.1.0
- Generation of PWM by software is active by default.
- Removed decode_results results.
- Renamed most irparams_struct values.
- Fixed LG send bug and added unit test.
- Replaced `#define DECODE_NEC 1/0` by defining/not defining.
- Use LED_BUILTIN instead of FEEDBACK_LED if FeedbackLEDPin is 0.
- Use F_CPU instead of SYSCLOCK.
- Removed SENDPIN_ON and SENDPIN_OFF macros.

- Refactored board specific code for timer and feedback LED.
- Extracted common LED feedback functions and implemented feedback for send.
- MATCH_MARK() etc. now available as matchMark().
- Added STM32F1 by (by Roger Clark) support.
- Added stm32 (by ST) support. Thanks to Paolo Malaspina.
- Added ATtiny88 support.

## 3.0.2
- Bug fix for USE_OLD_DECODE.
- Increase RECORD_GAP_MICROS to 11000.
- Fix overflow message. (#793).
- Improved handling for HASH decoder.
- Tested for ATtiny85.
- Added `printIRResultMinimal()`.
- Added missing IRAM_ATTR for ESP32.
- Adapted to TinyCore 0.0.7.
- Fixed decodeSony 20 bit bug #811.
- Replaced delayMicroseconds with customDelayMicroseconds and removed NoInterrupt() for send functions, removed SPIN_WAIT macro, sleepMicros() and sleepUntilMicros().
- Fixed LG checksum error.
- Fixed JVC repeat error.

## 3.0.0 + 3.0.1 2021/02
- New LSB first decoders are default.
- Added SendRaw with byte data.
- Fixed resume bug if irparams.rawlen >= RAW_BUFFER_LENGTH. Thanks to Iosif Peterfi
- Added `dumpPronto(String *aString, unsigned int frequency)` with String object as argument. Thanks to Iosif Peterfi
- Removed Test2 example.
- Fixed swapped cases in `getProtocolString()`. Thanks to Jim-2249
- Added compile option `IR_INPUT_IS_ACTIVE_HIGH`. Thanks to Jim-2249
- Corrected template. Thanks to Jim-2249
- Introduced standard decode and send functions.
- Added compatibility with tone for AVR's.
- New TinyIRreceiver does not require a timer.
- New MinimalReceiver and IRDispatcherDemo examples.
-0A$led TinqCO�e�10b!ATtiny3217 wu`rgrP*/ A�tgd(�rp&d r�gu�c/.&+*'#(2<1��0�:?sQ- Fixed bwg,h~"Son{ ldco`ek�nRCa=cEA�i.j:.*p�
a� *,8�0 r02�/1r=�pa.oed LicefsE$to m� @ga xvtps:�/g*T��r.goumave5�~^/IRremote/A�du+n�I0em�teLi#b4��/2)�l%!Adde` QVtibY�xm�s � s�`0grt./bCa`nget!��zg p%|urn cote`{igfiUq��4Nv#d�cnD��e|{ellstanceDqr!:*(`ne(�uw,�Aj&lyn'&-|[5govadpOiUs�bi1hh �roUc/d, Si�se Ti�impme�enUatyo.(9s` n B���r#&)ctHon0s)lj ann8m.kumentatiwf@ed�Mg�0a�� 6�eb/&Gve suppoce$*Tg�2E �bolg&- R�mw7ed AIWA implementctan., Ryl#e�iTgi�0�nl fgr(5�pev!cGE�oEb�4 .Dast t`ew=nDDog wak`	aQ�em'nted072gOw.B% Eddgd(Ye�eF�mEwk�,�!C+A��uE0i.|ernal usage$�~*A�G-t�|ixWuS�{((9#Mo�et�de/0'print functions bro0E8��p,/ to �rS'�e�ger*
="irPrOn�&c�t:CUsi�ghRLnt insde!� o  C�sE�m safe3(q02 �ypec"ppow!u0m-dory. la_eed drW��.b4g8"@XebcMd��r type pk0pg mnv�0~sA�spasg�|!ajd0aofsAwTan4 sdjotheR �de of K�zt-ote.

#" �.7.0 2020/08� Eel�D$ATmgFi"�@B sep e"to- RenaMe�0(irdware rp�ciniC$macRo�q�d $unatann nameq// Zdnamed `USEOSNU_�E�B[Eh, pU]�OCARRIER`, `ETН_CxCLe�}ccrNc!6�(cU[D_SOFT_SUNWTW]", AQSU]NO�SUWQW�`, `IS_�Int�TQTI]CxCHU`.
- Ve]m�ud(bLkckin_ �|i� for ATmeg`1�]}(sarial�i~b%pampLe�>
 �u!ktivatcd8edn�ult dAb�u0o%| y46(-�_� ioHzdD$tqpEw in rE��BC5ex �_d s�n`x�p A-}.�- IdEa� hOEkJDE_NECWStENDARD@ �^d�x[dJD_NEC_S\Af@aVD`.
- R�oa�ed(a\h`ARs%�rg�qmxLE�2tf!�RreceIv�:.
- Qd$md f�~�d�o^3�pxsintIPRmrqldqh�"t(Sefi1f)` ent"�ga@ro�n�=lSt�in%(decodetyQ�_�baEe�odeType)T.�7`Xd�m�0l�V�QdeaolddiR�qta/a�riqe`t�.J-`}teeee�(examrLm�>
�##b2.6.1 2020/00
$Adj5s|DD$V	an� Ĝ T/}i.o.
- Fixed 480;$jde.

##$2>4&0 0� .0�
'!�ed'da��Qkzt bor MagiQuest0Asen|q- C/rrDcted Samcu. 4ah{z-#PB�UG jgPaau �m0|�m,tat�On�-(Wo2e�4t)Oo a�d Ch�~�yng0`4A�U��CFIG_K@ZP%!�d `TI]G�B_NIg[NORMALap�!BrOw`tosx`dkc fulbt�Ojs.
-hIDaa� `RAMOA�L�b($o� MP32 I�R>J- Removef h�de$ine HAG_LRNTdRRSXLlL &�- �a~eD ��ce)~e3`�U@ve{/ N/w Rtarting$wyvh00o� Fh�lged switch0t/ iF$/ e�seBi�0in I�Re+o$g.Bp� "/bk�Z �oE MRP3r kNMtiler0b5o.
!AhiOg�t `DEB]G@$hcnlmi~g`{{l+d!koM�im'v w#Rl�`J)T8�EXp<p �IF" r`:EZE� spad�me<T#�9& ��b'�te(Chs>
H## 2.5.8 42�/0t
- Aozsec~eL%+eyTozes.vx|/
/ jn�tW�re2�{Uoko$aGd}e`YR�#v90�0�rmat4inFh�OL0|u!ll the"nmv"s|xlgs dEU�- Pebh=G`p�1�dug�s>lb8YISRU�(#S35|(https>/?e)thUb�coL�A�'u�~�o�rmlodeokr�di~o�ER gmotg/ar�ud1�3�5)
-�Re-a�ed `SE_E��IN` tk pKC_�MND_XInd.
� R'va	hu��tate%m�aros,%1GnablaD0�TUTY_CXC�Aa0�kb6quld signal.- Ed`et"qefehn� fo2 ErP22�
m CIan��$�@w,ef%jb]k }iNp8_t �o(7NwagOa� Ikp�qnlosi~e bIg�ur r�ca+fg fwvltr`il(�_n@mmd dRAWbM�.te!hScW�SUFFARONENGTH@.�=��nt0kfeadd$�E�E_NO^C�VR9_�1,for smmela�`~$an IR!s��g�}d0.
Chanee{!vr/e #28p�)	�fn�ulav5e�Rco.-!��d'D �eoc�aoN$re�dRaw_�(ijF.�0Renfiff data$fbm�0vn){h*
Wjpl�es �ro- +368 ��`+&amnh}lpxre1s+(OPpkma{ed by!r�fuk(ng�fl-mtYhg point oqe�ati~3hiS �e'oasdGd�ry$msbePn�q� 0 !9s!,
%"O|qy?+red wi�l�<c�ros when usiNg�tebi�Npb`MISPR^�ER_TIk@��~�0hUOLERA^C@.�9,N5n�"�7coTe�y�h cshd B�dtabld`�rFtOfm�(eDfilel!b{ hEECODE]HKR@a.
-"ALeet h�liQs Ex�en&ed Zc�4pb}t/kol sutrxu [PR #5:2�t(j\t�s://fi�lur,cmm'@rdui�o/�s5%Ota?Q0d}hn-$A�6emNteopeN,�40!#)!:/4,0(, "01?'+12 (��K�e�uPb�v!(mse�are depende.ciEs�"MmSg�0ao$QQG!cu0xort [PR�#�q7(http{:+wi4 qb��o/ordui.g-XV2mm�tDm�b�7i(o=KreLnt�/tu|n/$3w!

## 2&370-`z01/03/31
- Adde``UQq32 KR)s�cejf�akw0pnrt![�R`+427](ht4ps//Gh���z.Ckm/ArduanO�IR0elo�d/�rduino-IRremoteopuMl/425)

#c 22.3(, �05?�#g!�yx cclktl`p��!of"p)tsD he~�thbin L�O_@TF qr�unc�}a���H+�f7]	hut�s://gidh�j&!Oi�Ar&wifn-IS2�mNte/ARd�ydoLFremoue�zuDi?42?)+#A��.:a- 1�/01'0,`N�|e6"namanN$�qg [PR #388�*�t|w:,g��lu0,co�.C�ltI��?Js%eotE/�bltIn�?MZcem'e�NX7�to=8)

"#�2�r.1]=]x06�"73�-Dddcd8�es6s for`LeBoR�gep Jt~ation�(@ktgcO� [V 313>]m�pq:'.github.com/Arduino-ARVa]-�ez$}inoI�b�modeo|utn736)*
��7m��8,$2A�2r6/28
- Ad�U support0f/z ATmUf��531
= Aheuf sup�or2 vm�0AVeeca!4
%�a`&ed suppobp`~mr$QD�mg#32
- Added stp�kr$"fLr(@TmEg�!64
- Ad�%5`�ppNzd "gr ATmega2�0�xded �up2ort doz!ATodo�644
- QD$�T��%ppNrT!��rhHT�Af��284
= dded 3upQorv nnr ADm%oa24/@Id4gdsqp`m�t!$�r EU}��a3p8
_�BU(h�tPw:+/wkthub.com/Crltyn/%IRve}}t%'Qp$u`�O��re�ot7/0}ll/324i

# 2.q.1- 2006�05/04
-�Ed6gd Lewo`Zodr�Dm'btioNs�@rotocol [PR #309](https://gIt�%b.Bom/ar�%dn�+IRru-.|�'Qq@��>%-IRr%mou5� \ll/30)��+$�:1*80$2016/02/2p
-IM}��podAebuggioa�JS�&#:48](http*i�i��]$Lgo�'A`ui�o-Rreom�lnr�u�,o�KP8ldkTs-xtll/258)
- @icplix TI�E *n�Te�t og �IBK� [�b(���M(hpt`q://�it*ub.com/Ardti�o-IRramve/�r$7iO�-Iremote/pull/2549:L;#`:�0.v -0�p1u/02'2�-b@d� Pana�no��efe JVcF��RARreckrt"eximPh� [B]i`�tpq:'.'itHu�.�o}o�Lt�no-IRrmmNp�/Qr$}ino)IBpemodeoxt,�/�u)
/#7�"Lz�# - 2036'1/�$)Q�q�ve"i�uOd Ra er@le�er tg Ckns4 [yR}<h4|Ps��Km�niub.com/Arduino-IZrEiot�/A0duino�IR0emote/pull/227)

## 3.�.2 , �015/12/<2:) AgDie Yr2�}oteInfo Sie|bh - [PZ]ltt0s:.��dhub/c�m/Er4wiNo�IZrEiote/Ardukng,IRce�g�e/pu,m/�$1m=.>`��caLG�Rhangemo�.-l
3! 2.8.$-`205/07.2� o WruneaE��xTQps://github.cgmwhirriff.Afd5#lm%@Srem�teLrelda�a3?v@g/RE	i##!C�ang%s
"�xg'|tf README
 � `ated onUVi�gtors
- Dkple #110�Me1s
= z%ire|#GitTe�0Room
- Adddd�Gi|tEv BaDg�- Rt�ndarliSA�S-debCh��- Le�~ LU��nuv8ut+- Mp}h�i�ud`[gn|!gops-(L�du.arize$ DDsign
- Optimi~ed"!f` Artcte� E2aMtle{
$I-prNve� E-�umentatiOn�= Fi|gt*`nd(I]t2gwe� ma�y 1o$ang eprgss
/ NhxeD �yWe"RK,T501 Des$!f�
-bFixed Inters��4Jk.!A�megc8��C5klc(�d 6o S4aeM�#Release of1p��Eb�rM	�+)#
!Addipil{J$`ddee �i�q�Pc-�%p5 apktaol
- Added`Deo�8@potjc�N��Qd$m� X0O*�g1qppr4� A&ded C/�`�Meboptiojs/ Ad�dE�PUl��atd �or`NaV0�votocols-(@dded tlic"ch�lo�Mk%
m AEded Tee~s9(L� S5pxnrt*-�Qdded Q4aOy84 Sqp`mst�m ADd�d �Tt+ny85 Sep0crd- A`duf isIDl�0meuh�d
!�.!�e�utimn{	-(SM��b'd F�hE`)!#�11
�$bb�{e T%enRy 30/`�.Q|Sy�w24
+"#�0Not(WOfk)nw*i(eeMsq!3�/ P.! }rpgst"i{!yn`Lev�lo:mej�