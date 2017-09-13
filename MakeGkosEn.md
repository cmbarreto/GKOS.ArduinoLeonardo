<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
               "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<title>MakeGkosEn</title>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8"/>
<meta name="title" content="MakeGkosEn"/>
<meta name="generator" content="Org-mode"/>
<meta name="generated" content="2014-07-25 01:11:49 UTC"/>
<meta name="author" content=""/>
<meta name="description" content=""/>
<meta name="keywords" content=""/>
<style type="text/css">
 <!--/*--><![CDATA[/*><!--*/
  html { font-family: Times, serif; font-size: 12pt; }
  .title  { text-align: center; }
  .todo   { color: red; }
  .done   { color: green; }
  .tag    { background-color: #add8e6; font-weight:normal }
  .target { }
  .timestamp { color: #bebebe; }
  .timestamp-kwd { color: #5f9ea0; }
  .right  {margin-left:auto; margin-right:0px;  text-align:right;}
  .left   {margin-left:0px;  margin-right:auto; text-align:left;}
  .center {margin-left:auto; margin-right:auto; text-align:center;}
  p.verse { margin-left: 3% }
  pre {
	border: 1pt solid #AEBDCC;
	background-color: #F3F5F7;
	padding: 5pt;
	font-family: courier, monospace;
        font-size: 90%;
        overflow:auto;
  }
  table { border-collapse: collapse; }
  td, th { vertical-align: top;  }
  th.right  { text-align:center;  }
  th.left   { text-align:center;   }
  th.center { text-align:center; }
  td.right  { text-align:right;  }
  td.left   { text-align:left;   }
  td.center { text-align:center; }
  dt { font-weight: bold; }
  div.figure { padding: 0.5em; }
  div.figure p { text-align: center; }
  div.inlinetask {
    padding:10px;
    border:2px solid gray;
    margin:10px;
    background: #ffffcc;
  }
  textarea { overflow-x: auto; }
  .linenr { font-size:smaller }
  .code-highlighted {background-color:#ffff00;}
  .org-info-js_info-navigation { border-style:none; }
  #org-info-js_console-label { font-size:10px; font-weight:bold;
                               white-space:nowrap; }
  .org-info-js_search-highlight {background-color:#ffff00; color:#000000;
                                 font-weight:bold; }
  /*]]>*/-->
</style>
<script type="text/javascript">
<!--/*--><![CDATA[/*><!--*/
 function CodeHighlightOn(elem, id)
 {
   var target = document.getElementById(id);
   if(null != target) {
     elem.cacheClassElem = elem.className;
     elem.cacheClassTarget = target.className;
     target.className = "code-highlighted";
     elem.className   = "code-highlighted";
   }
 }
 function CodeHighlightOff(elem, id)
 {
   var target = document.getElementById(id);
   if(elem.cacheClassElem)
     elem.className = elem.cacheClassElem;
   if(elem.cacheClassTarget)
     target.className = elem.cacheClassTarget;
 }
/*]]>*///-->
</script>

</head>
<body>

<div id="preamble">

</div>

<div id="content">
<h1 class="title">MakeGkosEn</h1>


<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#sec-1">1 USB keyboard GKOS</a>
<ul>
<li><a href="#sec-1-1">1.1 Materials</a></li>
<li><a href="#sec-1-2">1.2 Software</a></li>
<li><a href="#sec-1-3">1.3 Procedure</a>
<ul>
<li><a href="#sec-1-3-1">1.3.1 Hardware</a></li>
<li><a href="#sec-1-3-2">1.3.2 Software</a></li>
</ul>
</li>
</ul>
</li>
</ul>
</div>
</div>

<div id="outline-container-1" class="outline-2">
<h2 id="sec-1"><span class="section-number-2">1</span> USB keyboard GKOS</h2>
<div class="outline-text-2" id="text-1">


</div>

<div id="outline-container-1-1" class="outline-3">
<h3 id="sec-1-1"><span class="section-number-3">1.1</span> Materials</h3>
<div class="outline-text-3" id="text-1-1">

<ul>
<li>1 - Arduino pro micro <a href="https://www.sparkfun.com/products/12640">https://www.sparkfun.com/products/12640</a>

</li>
<li>1 - 1K resistor 

</li>
<li>6 - Mouse Buttons (test them well if mouse are old) 

</li>
<li>1 - Breadboard welding 

</li>
<li>Other materials to build the "body" of the keyboard. 
</li>
</ul>


</div>

</div>

<div id="outline-container-1-2" class="outline-3">
<h3 id="sec-1-2"><span class="section-number-3">1.2</span> Software</h3>
<div class="outline-text-3" id="text-1-2">

<p>From this site we get the main software for the keyboard: <a href="http://gkos.com/gkos/arduino/index.html">http://gkos.com/gkos/arduino/index.html</a>
We repeat here the links. 
</p><ul>
<li>Java to run the Arduino IDE I use jre1.6.0. 
</li>
<li>GKOS library v.1.5 (2010-04-14) for Arduino IDE <a href="http://gkos.com/gkos/arduino/library/Gkos_library_2010-04-14.zip">http://gkos.com/gkos/arduino/library/Gkos_library_2010-04-14.zip</a> 
</li>
<li>Arduino Arduino IDE 1.0.5 <a href="http://arduino.cc/en/Main/Software # TOC2">http://arduino.cc/en/Main/Software # TOC2</a> 
</li>
<li>Also the software for pro micro  was obtained <a href="https://github.com/sparkfun/SF32u4_boards">https://github.com/sparkfun/SF32u4_boards</a>
</li>
</ul>


</div>

</div>

<div id="outline-container-1-3" class="outline-3">
<h3 id="sec-1-3"><span class="section-number-3">1.3</span> Procedure</h3>
<div class="outline-text-3" id="text-1-3">


</div>

<div id="outline-container-1-3-1" class="outline-4">
<h4 id="sec-1-3-1"><span class="section-number-4">1.3.1</span> Hardware</h4>
<div class="outline-text-4" id="text-1-3-1">

<p><img src="./IMG_20140724_104625_02.png"  alt="./IMG_20140724_104625_0.jpg" /> 
</p></div>

</div>

<div id="outline-container-1-3-2" class="outline-4">
<h4 id="sec-1-3-2"><span class="section-number-4">1.3.2</span> Software</h4>
<div class="outline-text-4" id="text-1-3-2">

<p>I did all this in Linux, but should work for other operating systems. 
</p><ul>
<li id="sec-1-3-2-1">Installing Arduino IDE<br/>
This leads us "arduino-1.0.5" directory with the files needed to use the Arduino IDE. 
</li>
</ul>
<ul>
<li id="sec-1-3-2-2">Unzip the library GKOS<br/>
Just unzip in "arduino-1.0.5/libraries" and get something like this: 



<pre class="example">ls -l arduino-1.0.5/libraries/
total 20
drwxr-xr-x 3 guest guest   72 May 17  2013 EEPROM/
drwxr-xr-x 3 guest guest   74 May 17  2013 Esplora/
drwxr-xr-x 4 guest guest 4096 May 17  2013 Ethernet/
drwxr-xr-x 3 guest guest  122 May 17  2013 Firmata/
drwxr-xr-x 3 guest guest 4096 May 17  2013 GSM/
drwxr-xr-x 3 guest guest  152 Jul 21 00:23 Gkos/
drwxr-xr-x 3 guest guest   86 May 17  2013 LiquidCrystal/
......
</pre>

</li>
</ul>
<ul>
<li id="sec-1-3-2-3">Run arduino IDE.<br/>
It is a Java program in "arduino-1.0.5/arduino" 
This opens up for the first time the Arduino IDE. 
If we look at the examples available we will meet the GKOS installed before. 
If I tried it now it will not run, a few steps missing. 
Open and recorded some test sketch, this creates us in our working directory "sketchbook" 



<pre class="example">ls -l sketchbook/
total 0
drwxr-xr-x 2 root  root  30 Jul 12 03:46 gkos_usb_keyb/
drwxr-xr-x 3 guest guest 33 Jul 13 01:43 hardware/
drwxr-xr-x 2 guest guest 23 Jul 12 03:04 libraries/
</pre>

</li>
</ul>
<ul>
<li id="sec-1-3-2-4">The software pro micro.<br/>
Under the hardware directory unzip the software for pro micro "sketchbook/hardware/SF32u4_boards-master" 
The next time we run the Arduino IDE we have available this model in the hardware list. 



</li>
</ul>
<ul>
<li id="sec-1-3-2-5">Files modified<br/>
"arduino-1.0.5/libraries/Gkos/Gkos.cpp" This is the modified file <a href="./Gkos.cpp">./Gkos.cpp</a> 
And the script arduino a modification of "arduino-1.0.5/libraries/Gkos/examples/gkos_serial01/gkos_serial01.pde"
became this: <a href="./gkos_usb_keyb.ino">./gkos_usb_keyb.ino</a> 
That is the one we open with the Arduino IDE to compile and install the software.

<p>
Thats all folks.
</p>
</li>
</ul>
</div>
</div>
</div>
</div>
</div>

<div id="postamble">
<p class="date">Date: 2014-07-25 01:11:49 UTC</p>
<p class="author">Author: </p>
<p class="creator">Org version 7.8.11 with Emacs version 24</p>
<a href="http://validator.w3.org/check?uri=referer">Validate XHTML 1.0</a>

</div>
</body>
</html>
