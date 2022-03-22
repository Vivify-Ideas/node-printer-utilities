const { getDefaultPrinter, sendToPrinter, initSettings, deinitSettings } = require(".");

// console.log(getDefaultPrinter());

const html = `data:text/html,<!DOCTYPE html><html xmlns="http://www.w3.org/1999/xhtml" lang="en"><head>
	<meta charset="UTF-8" />
	<title>Print Manager Template</title>
<style>.footer-ticket-description {
  text-align: center;
  display: flex;
  flex-direction: column;
}</style><style> @media print and (max-width: 10cm) {
      body: 100% !important;
      height: 100% !important;
    }
    @page {
       margin: 0 0 0 2mm;
    }
.text-truncate {
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
}
@font-face {
    font-family: "Roboto Condensed";
    font-style: normal;
    font-weight: 400;
    src: url(file:///tmp/ticketAssets/ieVl2ZhZI2eCN5jzbjEETS9weq8-59U.ttf) format("truetype");
}
@font-face {
    font-family: "Roboto Condensed";
    font-style: normal;
    font-weight: 700;
    src: url(file:///tmp/ticketAssets/ieVi2ZhZI2eCN5jzbjEETS9weq8-32meKCM.ttf) format("truetype");
}
body,
html {
    margin: 0 auto 2mm;
    padding: 0;
    background-color: white;
    color: black;
    font-family: "Roboto Condensed", monospace;
    font-size: 12px;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: antialiased;
    font-smoothing: antialiased;
}
header-section > .top {
    display: block;
    width: 100%;
}
.content-section,
.header-section > .top .top-wrapper,
body,
html {
    width: 100%;
}
.content-section .events .event.lucky .bot:after,
.content-section .events .event.lucky .bot:before,
.content-section .payment:after,
.content-section .payment:before,
.header-section > .top .top-wrapper:after,
.header-section > .top .top-wrapper:before {
    content: " ";
    display: table;
}
.content-section .events .event.lucky .bot:after,
.content-section .payment:after,
.header-section > .top .top-wrapper:after {
    clear: both;
}
.header-section > .top .top-wrapper .logo {
    float: left;
    width: 100%;
    background-color: black;
    color: white;
}
.header-section > .top .top-wrapper .logo img {
    display: block;
    width: 160px;
    margin: 5px auto 0;
}
.header-section > .mid,
.header-section > .top .top-wrapper .logo p {
    margin: 5px 0;
    text-align: center;
}
.header-section > .top .top-wrapper .qrcode {
    display: none;
}
.header-section > .mid {
    display: block;
    width: 100%;
    margin: 0;
    font-size: 8pt;
    border-bottom: 1pt solid black;
}
.header-section > .mid .info-block {
    display: block;
    padding: 0;
    color: black;
    text-align: center;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
}
.header-section > .mid .info-block:last-child {
    border-bottom: none;
}
.header-section > .mid .info-block .label {
    display: none;
    float: left;
    height: 20px;
    text-align: center;
}
.header-section > .mid .info-block .label img {
    display: block;
    width: 16px;
    margin: 0;
}
.header-section > .mid .info-block .text {
    text-align: center;
    line-height: 12px;
}
.header-section > .bot {
    display: block;
    width: 100%;
    margin-top: 5px;
}
.header-section > .bot .promotion {
    display: none;
    width: 100%;
    margin: 4px 0;
    border-bottom: 1px solid black;
    text-align: center;
    word-wrap: break-word;
}
.header-section > .bot .promotion .title {
    padding: 2px 0;
    background-color: black;
    color: white;
    text-transform: uppercase;
}
.header-section > .bot .promotion .content {
    padding: 4px;
    font-size: 12px;
    line-height: 13px;
}
.header-section .barcode {
    width: 100%;
    margin: 4pt 0;
}
.header-section .barcode div.barcode-value {
    display: block;
    width: 70%;
    height: 30px;
    margin: 0 15%;
    color: white;
    text-indent: -9999px;
}
.header-section .barcode span.barcode-value {
    display: block;
    width: 100%;
    color: black;
    font-size: 9pt;
    letter-spacing: 2pt;
    text-align: center;
}
.header-section .payout-code {
    width: 100%;
    border-top: 1pt solid black;
    font-size: 10pt;
    text-align: center;
}
.header-section .payout-code > div {
    display: inline;
}
.content-section .payment .date span,
.header-section .payout-code .value {
    font-weight: 700;
}
.content-section .events {
    border-top: 4pt solid black;
}
.content-section .events .multi-wrapper {
    border-bottom: 4pt solid black;
    margin-bottom: 1pt;
}
.content-section .events .multi {
    width: 96%;
    padding: 0 2%;
    border-top: 4pt solid black;
    color: black;
    font-size: 12px;
    text-align: center;
    text-transform: uppercase;
}
.content-section .events .event {
    position: relative;
    width: 100%;
    border-top: 1pt solid black;
}
.content-section .events .event:first-child {
    border-top: none;
}
.content-section .events .event > div {
    line-height: normal;
}
.content-section .events .event.sport .top {
    font-size: 8pt;
    line-height: normal;
    text-transform: uppercase;
}
.content-section .events .event.sport .top > div {
    display: inline-block;
    word-wrap: break-word;
}
.content-section .events .event.sport .top .time-date {
    margin: 0 1pt;
}
.content-section .events .event.sport .top .id {
    font-size: 10pt;
    font-weight: 700;
}
.content-section .events .event.sport .mid {
    font-size: 10pt;
    text-transform: uppercase;
}
.content-section .events .event.sport .mid > div {
    display: inline-block;
}
.content-section .events .event.empty-bet .mid .home:after,
.content-section .events .event.live .mid .home:after,
.content-section .events .event.racing .mid .home:after,
.content-section .events .event.sport .mid .home:after {
    display: inline;
    content: " - ";
    width: auto;
}
.content-section .events .event.sport .bot {
    position: relative;
    padding-right: 8mm;
    font-size: 9pt;
}
.content-section .events .event.sport .bot > div {
    display: inline;
}
.content-section .events .event.sport .bot .odd {
    position: absolute;
    bottom: 0;
    right: 0;
}
.content-section .events .event.live {
    position: relative;
}
.content-section .events .event.live:before {
    position: absolute;
    display: block;
    content: "LIVE";
    width: auto;
    height: 16px;
    top: 1mm;
    right: 0.5mm;
    padding: 0 1mm;
    border: 1pt solid black;
    font-size: 8pt;
    line-height: 18px;
    border-radius: 4px;
}
.content-section .events .event.live .top {
    padding-right: 8mm;
    font-size: 8pt;
    line-height: normal;
    text-transform: uppercase;
}
.content-section .events .event.live .mid > div,
.content-section .events .event.live .top > div {
    display: inline-block;
}
.content-section .events .event.live .top .id {
    font-size: 10pt;
    font-weight: 700;
}
.content-section .events .event.live .mid {
    padding-right: 8mm;
    font-size: 10pt;
    text-transform: uppercase;
}
.content-section .events .event.live .bot {
    position: relative;
    padding-right: 8mm;
    font-size: 9pt;
}
.content-section .events .event.live .bot > div {
    display: inline;
}
.content-section .events .event.empty-bet .bot .odd,
.content-section .events .event.live .bot .odd {
    position: absolute;
    bottom: 0;
    right: 0;
}
.content-section .events .event.empty-bet .mid {
    font-size: 10pt;
    text-transform: uppercase;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
}
.content-section .events .event.empty-bet .mid > div {
    display: inline-block;
}
.content-section .events .event.empty-bet .bot {
    position: relative;
    padding-right: 10mm;
    font-size: 9pt;
}
.content-section .events .event.empty-bet .bot > div {
    display: inline;
}
.content-section .events .event.keno .top {
    font-size: 8pt;
}
.content-section .events .event.keno .mid > div,
.content-section .events .event.keno .top > div,
.content-section .events .event.lucky .mid > div,
.content-section .events .event.lucky .top > div,
.content-section .events .event.racing .mid > div,
.content-section .events .event.racing .top > div {
    display: inline-block;
}
.content-section .events .event.keno .top .time-date {
    margin: 0 1pt;
}
.content-section .events .event.keno .top .drawing {
    font-size: 10pt;
    font-weight: 700;
}
.content-section .events .event.keno .mid {
    font-size: 10pt;
    text-transform: uppercase;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
}
.content-section .events .event.keno .bot {
    position: relative;
    text-align: lfet;
}
.content-section .events .event.keno .bot .game {
    font-size: 9pt;
    text-align: left;
}
.content-section .events .event.keno .bot .selection,
.content-section .events .event.keno .bot .value {
    display: inline-block;
    font-size: 9pt;
    text-align: left;
}
.content-section .events .event.keno .bot .odd {
    position: absolute;
    top: 0;
    right: 0;
    font-size: 9pt;
}
.content-section .events .event.keno .bot .ball {
    display: inline-block;
    width: 18pt;
    height: 18pt;
    margin-top: 1pt;
    margin-bottom: 1pt;
    margin-right: 1pt;
    border: 1pt solid black;
    border-radius: 50%;
    font-size: 10pt;
    line-height: 20pt;
    text-align: center;
}
.content-section .events .event.lucky .top {
    font-size: 8pt;
}
.content-section .events .event.lucky .top .time-date {
    margin: 0 1pt;
}
.content-section .events .event.lucky .top .drawing {
    font-size: 10pt;
    font-weight: 700;
}
.content-section .events .event.lucky .mid {
    font-size: 10pt;
    text-transform: uppercase;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
}
.content-section .events .event.lucky .bot {
    position: relative;
    text-align: left;
}
.content-section .events .event.lucky .bot .game {
    font-size: 9pt;
    text-align: left;
}
.content-section .events .event.lucky .bot .selection {
    margin-left: 4px;
    float: left;
    font-size: 9pt;
    text-align: left;
}
.content-section .events .event.lucky .bot .value {
    float: left;
    font-size: 9pt;
    text-align: left;
}
.content-section .events .event.lucky .bot .odd {
    position: absolute;
    top: 0;
    right: 0;
    font-size: 9pt;
}
.content-section .events .event.lucky .bot .ball {
    display: inline-block;
    width: 18pt;
    height: 18pt;
    margin-top: 1pt;
    margin-right: 1pt;
    border: 1pt solid black;
    border-radius: 50%;
    font-size: 10pt;
    line-height: 20pt;
    text-align: center;
}
.content-section .events .event.racing .mid,
.content-section .events .event.racing .top {
    text-transform: uppercase;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
}
.content-section .events .event.racing .top {
    font-size: 8pt;
    line-height: normal;
}
.content-section .events .event.racing .top .time-date {
    margin: 0 1pt;
}
.content-section .events .event.racing .top .id {
    font-size: 10pt;
    font-weight: 700;
}
.content-section .events .event.racing .mid {
    font-size: 10pt;
}
.content-section .events .event.racing .bot {
    position: relative;
    font-size: 9pt;
}
.content-section .events .event.racing .bot > div {
    display: inline;
}
.content-section .events .event.racing .bot .odd {
    position: absolute;
    top: 0;
    right: 0;
}
.content-section .events .event.racing .bot .price {
    position: absolute;
    top: 0;
    right: 10mm;
}
.content-section .events .event .bot,
.content-section .lucky-table tr {
    border-bottom: 1pt solid black;
}
.content-section .events .event .bot:last-child,
.content-section .lucky-table tr td:last-child,
.content-section .lucky-table tr th:last-child {
    border: 0;
}
.content-section .lucky-table {
    width: 100%;
    margin-top: 2mm;
    text-align: center;
    border-collapse: collapse;
    border: 1px solid black;
}
.content-section .lucky-table tr td,
.content-section .lucky-table tr th {
    border-right: 1pt solid black;
    font-weight: 400;
}
.content-section .lucky-table tr th {
    background-color: black;
    color: white;
}
.content-section .payment {
    width: 100%;
    margin-top: 2mm;
    border-top: 4pt solid black;
    border-bottom: none;
}
.content-section .payment .data,
.content-section .payment .date {
    width: 100%;
    padding: 1px 0;
    border-bottom: 1px solid black;
}
.content-section .payment .date {
    font-size: 12px;
    text-align: center;
}
.content-section .payment .data {
    text-align: right;
}
.content-section .payment .data:after,
.content-section .payment .data:before {
    content: " ";
    display: table;
}
.content-section .payment .data:after {
    clear: both;
}
.content-section .payment .data .label,
.content-section .payment .data .value {
    display: inline-block;
    width: 45%;
    font-size: 10pt;
}
.content-section .payment .data .description span,
.content-section .payment .data .value {
    font-weight: 700;
}
.content-section .payment .data .description {
    width: 100%;
    padding: 5px 0;
    border-top: 1px dashed black;
    font-family: "Roboto Condensed", monospace;
    font-size: 10pt;
    line-height: 10pt;
    text-align: center;
}
.content-section .payment .data.special .label,
.content-section .payment .data.special .value {
    font-size: 14pt;
    font-weight: 700;
    text-transform: uppercase;
}
.content-section .payment .data.bonus:first-child {
    border-top: 4pt solid black;
}
.content-section .payment .data.bonus:last-child {
    border-bottom: 4pt solid black;
}
.footer-section {
    padding: 3mm 4mm;
    margin-top: 2mm;
    border-top: 1pt dashed black;
    border-bottom: 1pt dashed black;
    color: black;
    font-size: 9pt;
    font-weight: 400;
    line-height: 12px;
    text-align: center;
    word-wrap: break-word;
}
.footer-section img {
    display: block;
    margin: 0;
    padding: 0;
    width: 100%;
    height: auto;
}
@media print {
    body {
        margin: 0 auto !important;
        padding: 0 !important;
        orientation: portrait;
    }
}</style></head>
<body class="small-ticket">
	<div class="header-section">
      
    <div class="top">
      <div class="top-wrapper">
        <div class="logo">
          <img src="data:image/*;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAAAyCAMAAAAuj2TTAAAC9FBMVEUAAAD///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////9JxXEjAAAA+3RSTlMAAQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFDREVGR0hJSktMTU9QUVJTVFVWV1hZWltc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" />
          <p>The biggest bonuses</p>
        </div>

    
      <div class="bot">
        <div class="promotion">
          <div class="title">Promotion</div>
          <div class="content">Promotion description</div>
        </div> <!-- end of promotion -->
      </div> <!-- end of bot -->
      
      <div style="display: flex; flex-direction: column; align-items: center;">
        <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAABGCAYAAACJ4ts2AAADRklEQVR4Xu3dwXLDIAwE0Ob/PzqdaeJOjC2vzPRUXo9x7IaFhdVK4Mfz+Xx++YMABE4ReCCIkQGBGgEEMTogcIEAghgeEEAQYwACcwhYQeZwc9ciCCDIIh2tmXMIIMgcbu5aBAEEWaSjNXMOAQSZw81diyDQJsjj8dhBsiXgt8/HhHz1+Yjr7P3V79mePz53/P72vbEdVb9X30ufV+2t/v/d51Xt7X4+/o7Z/qnwvfv81K9ju8bfW43L7nMP7e9m0hHkVZGTcOgOCAR5IZAmsqoSqjvhzU44v0REkPOBn2amtAJ1O/avZry7K3F3Ru0+1wpCYllBPmaNNPNXE0yScHeJmyYyK8gboRQDdZdkMcgeAStIs9w9ae80QKuB1+2AbrBbBacIst/VcHemTv1LYpFYJBaJVc3z2b1JM4wVZO/acLG4WD8IJAVHYu1dtNmg8i6OJFZvI61E4XvHcVdDp1hMHuRcKyTb++7E0I0p7z73EOvKg8iDXK303ZWpO8Gwed8IVMAmgCoXiot1LQm6A3nEt7vipRgTQbhYXCwuFhdLolCi8BMBQbog/dJt7Eo3EovEIrFILBKLxCKxSKwPBGyYeoHRzVNULiOJRWKRWCQWiUVikVgkFolVbh2eTeSSWCQWiUVikVgkFolFYpFYJFbzvVEy6TLpbN5aOH0hCIIgCIIctwxvmEgUShRe8MMKgiAIgiAnR4ZaQc7PWpYHGVw8W25tuVWLdZHeQBAEQRAEOfj+JBaJdRV7bNfYvGxeNi+bl81bnUoyrqSCdEH6DgE2L5uXzcvmPewYdPSoo0d32rp7VKVqXtW8qnlV86rmVc37sjFTjJGuJzv47uHI6fDru8/7tSPfG9rSEaHj9wXp12Yvm5fNy+Zl87J52by9xOjB5lZqotREqYlSE6UmQ1DK5mXzCtI/8j8kFom1Wye7L7rnYsmky6TLpMukF+e6pYpeNi+bl83L5mXzikHEIGKQk9cYpDdEyaTLpP8goFhxb2uyef/Y5k3BjOsQ+I8ItIP0/9h4bYJAQgBBEkKuL40Agizd/RqfEECQhJDrSyOAIEt3v8YnBBAkIeT60gggyNLdr/EJAQRJCLm+NAIIsnT3a3xC4BvnDb4QcMlY5wAAAABJRU5ErkJggg==" />
        <span>317007</span>
      </div>
      
      
      <div class="payout-code">
        <div class="label">Payout code:</div>
        <div class="value">880572</div>
      </div>
    
      
		
	</div>
	<div class="content-section">
		<div class="events">
        <div class="multi">
          1/2 System
        </div>
        
      <div class="event sport">
        <div class="top">
          <div class="id">2099</div>
          <div class="time-date">
            19/03 19:00
          </div>
          <div class="league">
            Argentine Argentine Primera Division Women
          </div>
        </div>
        <div class="mid">
          <div class="home">
            Estudiantes de La Plata (W)
          </div>
          
              <div class="away">
                SATSAID (W)
              </div>
        </div>
        
      <div class="bot">
        <div class="game-name">
           Final Score
        </div>
        
        <div class="selection">
          X
        </div>
        <div class="odd">
          4.50
        </div>
      </div>
    
      <div class="bot">
        <div class="game-name">
           Final Score
        </div>
        
        <div class="selection">
          1
        </div>
        <div class="odd">
          1.68
        </div>
      </div>
    
      </div>
    
      
        <div class="multi">
          1/2 System
        </div>
        
      <div class="event sport">
        <div class="top">
          <div class="id">0425</div>
          <div class="time-date">
            19/03 20:00
          </div>
          <div class="league">
            Argentine Argentine Primera Division Women
          </div>
        </div>
        <div class="mid">
          <div class="home">
            Boca Juniors (W)
          </div>
          
              <div class="away">
                Villa San Carlos (W)
              </div>
        </div>
        
      <div class="bot">
        <div class="game-name">
           Final Score
        </div>
        
        <div class="selection">
          1
        </div>
        <div class="odd">
          1.03
        </div>
      </div>
    
      <div class="bot">
        <div class="game-name">
           Final Score
        </div>
        
        <div class="selection">
          X
        </div>
        <div class="odd">
          17
        </div>
      </div>
    
      </div>
    
      
        <div class="multi">
          1/5 System
        </div>
        
      <div class="event racing">
        <div class="top">
          <div class="id">
            504126
          </div>
          <div class="time-date">
            18/03 21:02
          </div>
        </div>
        <div class="mid">
          Virtual Dogs
        </div>
        
        <div class="bot">
          <div class="game-name">
            Forecast 
          </div>
          <div class="selection">
            2-1
          </div>
          <div class="odd">
            70.96
          </div>
        </div>
      
      </div>
    
      <div class="event racing">
        <div class="top">
          <div class="id">
            504126
          </div>
          <div class="time-date">
            18/03 21:02
          </div>
        </div>
        <div class="mid">
          Virtual Dogs
        </div>
        
        <div class="bot">
          <div class="game-name">
            Forecast 
          </div>
          <div class="selection">
            2-3
          </div>
          <div class="odd">
            26.98
          </div>
        </div>
      
      </div>
    
      <div class="event racing">
        <div class="top">
          <div class="id">
            504126
          </div>
          <div class="time-date">
            18/03 21:02
          </div>
        </div>
        <div class="mid">
          Virtual Dogs
        </div>
        
        <div class="bot">
          <div class="game-name">
            Forecast 
          </div>
          <div class="selection">
            2-4
          </div>
          <div class="odd">
            25.24
          </div>
        </div>
      
      </div>
    
      <div class="event racing">
        <div class="top">
          <div class="id">
            504126
          </div>
          <div class="time-date">
            18/03 21:02
          </div>
        </div>
        <div class="mid">
          Virtual Dogs
        </div>
        
        <div class="bot">
          <div class="game-name">
            Forecast 
          </div>
          <div class="selection">
            2-5
          </div>
          <div class="odd">
            79.90
          </div>
        </div>
      
      </div>
    
      <div class="event racing">
        <div class="top">
          <div class="id">
            504126
          </div>
          <div class="time-date">
            18/03 21:02
          </div>
        </div>
        <div class="mid">
          Virtual Dogs
        </div>
        
        <div class="bot">
          <div class="game-name">
            Forecast 
          </div>
          <div class="selection">
            2-6
          </div>
          <div class="odd">
            54.35
          </div>
        </div>
      
      </div>
    
      
		</div> <!-- end of events -->
		<div class="payment">
      
      <div class="date">
        Friday 18/03/2022 21:01:34 -
        Vladimir
      </div>
    
      
      
      <div class="data">
        <div class="label">Payin:</div>
        <div class="value">30<span> RSD </span></div>
      </div>
    
      
      <div class="data">
        <div class="label">Number of combinations:</div>
        <div class="value">20</div>
      </div>
    
      
      <div class="data">
        <div class="label">Min payout:</div>
        <div class="value">65.49
          <span> RSD </span>
        </div>
      </div>
    
      <div class="data">
        <div class="label">Max payout:</div>
        <div class="value">43019.90
          <span> RSD </span>
        </div>
      </div>

		</div> <!-- end of payment -->
	</div> <!-- end of content -->
	<div class="footer-section">p&gt; Gardez vos ticket non gagnant, <p></p>
<p>tous les mardis vient</p>
<p>Numéro de Jackpot.</p>
<p>Turbo paiement, accélérer vos gains!!!</p>
<p>Call Center: +237 678748588</p>
<p>+237 693485584</p>
<p>"Un client qui place un pari chez Supergooal est considéré comme</p>
<p>ayant lu et accepté ses règles. Cf. art. 1à 5 du livre des règles."</p>
	</div> <!-- end of footer -->

 </body></html>`

 initSettings();
console.log(sendToPrinter(html, "15cm", "10.4cm"));
