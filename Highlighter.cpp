#include "Highlighter.h"
#include <QSyntaxHighlighter>

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent){
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    QStringList keywordPatterns;
    keywordPatterns << "\\baaa\\b"<< "\\baad\\b"<< "\\baam\\b"
                    << "\\baas\\b"<< "\\badc\\b"<< "\\badd\\b"
                    << "\\band\\b"<< "\\barpl\\b"<< "\\bbound\\b"
                    << "\\bbsf\\b"<< "\\bbsr\\b"<< "\\bbswap\\b"
                    << "\\bbt\\b"<< "\\bbtc\\b"<< "\\bbtr\\b"<< "\\bbts\\b"
                    << "\\bcall\\b"<< "\\bcbw\\b"<< "\\bcdq\\b"
                    << "\\bclc\\b"<< "\\bcld\\b"<< "\\bcli\\b"<< "\\bclts\\b"
                    << "\\bcmc\\b"<< "\\bcmp\\b"<< "\\bcmps\\b"<< "\\bcmpsb\\b"
                    << "\\bcmpsd\\b"<< "\\bcmpsw\\b"<< "\\bcmpxchg\\b"<< "\\bcwd\\b"
                    << "\\bcwde\\b"<< "\\bdaa\\b"<< "\\bdas\\b"<< "\\bdec\\b"
                    << "\\bdiv\\b"<< "\\benter\\b"<< "\\bf2xm1\\b"<< "\\bfabs\\b"
                    << "\\bfadd\\b"<< "\\bfaddp\\b"<< "\\bfbld\\b"<< "\\bfbstp\\b"
                    << "\\bfchs\\b"<< "\\bfclex\\b"<< "\\bfcmovb\\b"
                    << "\\bfcmovbe\\b"<< "\\bfcmove\\b"<< "\\bfcmovnb\\b"
                    << "\\bfcmovnbe\\b"<< "\\bfcmovne\\b"<< "\\bfcmovnu\\b"
                    << "\\bfcmovu\\b"<< "\\bfcom\\b"<< "\\bfcomi\\b"<< "\\bfcomip\\b"
                    << "\\bfcomp\\b"<< "\\bfcompp\\b"<< "\\bfcos\\b"<< "\\bfdecstp\\b"
                    << "\\bfdiv\\b"<< "\\bfdivp\\b"<< "\\bfdivr\\b"
                    << "\\bfdivrp\\b"<< "\\bfemms\\b"<< "\\bffree\\b"
                    << "\\bfiadd\\b"<< "\\bficom\\b"<< "\\bficomp\\b"
                    << "\\bfidiv\\b"<< "\\bfidivr\\b"<< "\\bfild\\b"
                    << "\\bfimul\\b"<< "\\bfincstp\\b"<< "\\bfinit\\b"
                    << "\\bfist\\b"<< "\\bfistp\\b"<< "\\bfisub\\b"
                    << "\\bfisubr\\b"<< "\\bfld\\b"<< "\\bfld1\\b"
                    << "\\bfldcw\\b"<< "\\bfldenv\\b"<< "\\bfldl2e\\b"
                    << "\\bfldl2t\\b"<< "\\bfldlg2\\b"<< "\\bfldln2\\b"
                    << "\\bfldpi\\b"<< "\\bfldz\\b"<< "\\bfmul\\b"<< "\\bfmulp\\b"
                    << "\\bfnclex\\b"<< "\\bfninit\\b"<< "\\bfnop\\b"<< "\\bfnsave\\b"
                    << "\\bfnstcw\\b"<< "\\bfnstenv\\b"<< "\\bfnstsw\\b"
                    << "\\bfpatan\\b"<< "\\bfprem1\\b"<< "\\bfptan\\b"<< "\\bfrndint\\b"
                    << "\\bfrstor\\b"<< "\\bfsave\\b"<< "\\bfscale\\b"<< "\\bfsin\\b"
                    << "\\bfsincos\\b"<< "\\bfsqrt\\b"<< "\\bfst\\b"<< "\\bfstcw\\b"
                    << "\\bfstenv\\b"<< "\\bfstp\\b"<< "\\bfstsw\\b"<< "\\bfsub\\b"
                    << "\\bfsubp\\b"<< "\\bfsubr\\b"<< "\\bfsubrp\\b"<< "\\bftst\\b"
                    << "\\bfucom\\b"<< "\\bfucomi\\b"<< "\\bfucomip\\b"<< "\\bfucomp\\b"
                    << "\\bfucompp\\b"<< "\\bfwait\\b"<< "\\bfxch\\b"<< "\\bfxtract\\b"
                    << "\\bfyl2xp1\\b"<< "\\bhlt\\b"<< "\\bidiv\\b"<< "\\bimul\\b"
                    << "\\bin\\b"<< "\\binc\\b"<< "\\bins\\b"<< "\\binsb\\b"<< "\\binsd\\b"
                    << "\\binsw\\b"<< "\\bint\\b"<< "\\binto\\b"<< "\\binvd\\b"
                    << "\\binvlpg\\b"<< "\\biret\\b"<< "\\biretd\\b"<< "\\biretw\\b"
                    << "\\bja\\b"<< "\\bjae\\b"<< "\\bjb\\b"<< "\\bjbe\\b"<< "\\bjc\\b"
                    << "\\bjcxz\\b"<< "\\bje\\b"<< "\\bjecxz\\b"<< "\\bjg\\b"
                    << "\\bjge\\b"<< "\\bjl\\b"<< "\\bjz\\b"<< "\\bjg\\b"
                    << "\\bjge\\b"<< "\\bjl\\b"<< "\\bjle\\b"<< "\\bjna\\b"
                    << "\\bjnae\\b"<< "\\bjnb\\b"<< "\\bjnbe\\b"<< "\\bjnc\\b"
                    << "\\bjne\\b"<< "\\bjng\\b"<< "\\bjnge\\b"<< "\\bjnl\\b"
                    << "\\bjnle\\b"<< "\\bjno\\b"<< "\\bjnp\\b"<< "\\bjns\\b"
                    << "\\bjnz\\b"<< "\\bjo\\b"<< "\\bjp\\b"<< "\\bjpe\\b"
                    << "\\bjpo\\b"<< "\\bjs\\b"<< "\\bjmplahf\\b"<< "\\blar\\b"
                    << "\\blea\\b"<< "\\bleave\\b"<< "\\blgdt\\b"<< "\\blidt\\b"
                    << "\\blgs\\b"<< "\\blss\\b"<< "\\blfs\\b"<< "\\blds\\b"
                    << "\\bles\\b"<< "\\blldt\\b"<< "\\blmsw\\b"<< "\\block\\b"
                    << "\\blods\\b"<< "\\blodsb\\b"<< "\\blodsd\\b"<< "\\blodsw\\b"
                    << "\\bloop\\b"<< "\\bloope\\b"<< "\\bloopne\\b"<< "\\bloopnz\\b"
                    << "\\bloopz\\b"<< "\\blsl\\b"<< "\\bltr\\b"<< "\\bmov\\b"
                    << "\\bmovs\\b"<< "\\bmovsb\\b"<< "\\bmovsw\\b"<< "\\bmovsd\\b"
                    << "\\bmovsx\\b"<< "\\bmovzx\\b"<< "\\bmul\\b"<< "\\bneg\\b"
                    << "\\bnop\\b"<< "\\bnot\\b"<< "\\bor\\b"<< "\\bout\\b"
                    << "\\bouts\\b"<< "\\boutsb\\b"<< "\\boutsd\\b"<< "\\boutsw\\b"
                    << "\\bpop\\b"<< "\\bpopa\\b"<< "\\bpopad\\b"<< "\\bpopaw\\b"
                    << "\\bpopf\\b"<< "\\bpopfd\\b"<< "\\bpopfw\\b"<< "\\bpush\\b"
                    << "\\bpusha\\b"<< "\\bpushad\\b"<< "\\bpushaw\\b"<< "\\bpushf\\b"
                    << "\\bpushfd\\b"<< "\\bpushfw\\b"<< "\\brcl\\b"<< "\\brcr\\b"
                    << "\\brol\\b"<< "\\bror\\b"<< "\\brep\\b"<< "\\brepe\\b"
                    << "\\brepne\\b"<< "\\brepnz\\b"<< "\\brepz\\b"<< "\\bret\\b"
                    << "\\bsahf\\b"<< "\\bsal\\b"<< "\\bsar\\b"<< "\\bshl\\b"
                    << "\\bshr\\b"<< "\\bsbb\\b"<< "\\bscasd\\b"<< "\\bscasw\\b"
                    << "\\bseta\\b"<< "\\bsetae\\b"<< "\\bsetb\\b"<< "\\bsetbe\\b"
                    << "\\bsetc\\b"<< "\\bsete\\b"<< "\\bsetg\\b"<< "\\bsetge\\b"
                    << "\\bsetl\\b"<< "\\bsetle\\b"<< "\\bsetna\\b"<< "\\bsetnae\\b"
                    << "\\bsetnb\\b"<< "\\bsetnbe\\b"<< "\\bsetnc\\b"<< "\\bsetne\\b"
                    << "\\bsetng\\b"<< "\\bsetnge\\b"<< "\\bsetnl\\b"<< "\\bsetnle\\b"
                    << "\\bsetno\\b"<< "\\bsetnp\\b"<< "\\bsetns\\b"<< "\\bsetnz\\b"
                    << "\\bseto\\b"<< "\\bsetp\\b"<< "\\bsetpe\\b"<< "\\bsetpo\\b"
                    << "\\bsets\\b"<< "\\bsetz\\b"<< "\\bsgdt\\b"<< "\\bsidt\\b"
                    << "\\bshld\\b"<< "\\bshrd\\b"<< "\\bsldt\\b"<< "\\bsmsw\\b"
                    << "\\bstc\\b"<< "\\bstd\\b"<< "\\bsti\\b"<< "\\bstos\\b"
                    << "\\bstosb\\b"<< "\\bstosd\\b"<< "\\bstosw\\b"<< "\\bstr\\b"
                    << "\\bsub\\b"<< "\\btest\\b"<< "\\bverr\\b"<< "\\bverw\\b"
                    << "\\bwait\\b"<< "\\bwbinvd\\b"<< "\\bxadd\\b"<< "\\bxchg\\b"
                    << "\\bxlat\\b"<< "\\bxlatb\\b"<< "\\bxor\\b";


    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }





    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp(";[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
}
