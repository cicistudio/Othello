'copyright by cici studio @2004
'www.chengchen.net 程晨
'巧妙利用三维数组（x，y，判断的值）为0时放x的坐标，1为y的坐标，2为放子的判断。
'(x,y,2)=0未放子 (x,y,2)=1黑 (x,y,2)=2白
_TITLE ("五子风云v0.5 - www.chengchen.net")
DECLARE SUB youwin ()
DECLARE SUB youlose ()
DECLARE SUB logo ()
DECLARE SUB endlogo ()
DECLARE SUB pccheck1chess ()
DECLARE SUB pccheck2chess ()
DECLARE SUB checkpc3chess ()
DECLARE SUB checkmanwin ()
DECLARE SUB checkpc4chess ()
DECLARE SUB checkcomputerwin ()
DECLARE SUB juniorcomputer ()
DECLARE SUB juniorman ()
DECLARE SUB junior ()
DECLARE SUB main ()
DECLARE SUB senior ()
DECLARE SUB help ()
DECLARE SUB hzk24 (x%, y%, colo!, word$)
DIM SHARED xy(15, 15, 2)
COMMON SHARED x00, y00, checkpc3, check3
SCREEN 12
CALL logo
CLS
a = 82
FOR x = 1 TO 15
    a = a + 30
    FOR y = 1 TO 15
        xy(x, y, 0) = a '给三维数组存坐标
    NEXT y
NEXT x
a = -13
FOR y = 1 TO 15
    a = a + 30
    FOR x = 1 TO 15
        xy(x, y, 1) = a
    NEXT x
NEXT y
x0 = 200
p1 = 12: p2 = 11: p3 = 11: p4 = 11 '通过这种设计改变颜色，实现动态效果
LINE (190, 195)-(255, 300), 9, BF
LINE (192, 197)-(253, 298), 0, B
pp:
CALL hzk24(200, 200, p1, "初级")
CALL hzk24(200, 225, p2, "高级")
CALL hzk24(200, 250, p3, "版权")
CALL hzk24(200, 275, p4, "退出")

10 a$ = INKEY$: IF a$ = "" THEN 10
a$ = RIGHT$(a$, 1) '上为H,下为P,左为K,右为M.
IF a$ = "P" AND x0 < 275 THEN
    x0 = x0 + 25
    IF x0 = 225 THEN p2 = 12: p1 = 11
    IF x0 = 250 THEN p3 = 12: p2 = 11
    IF x0 = 275 THEN p4 = 12: p3 = 11
END IF
IF a$ = "H" AND x0 > 200 THEN
    x0 = x0 - 25
    IF x0 = 200 THEN p1 = 12: p2 = 11
    IF x0 = 225 THEN p2 = 12: p3 = 11
    IF x0 = 250 THEN p3 = 12: p4 = 11
END IF
IF a$ = CHR$(27) THEN CALL endlogo 'press esc
IF a$ = CHR$(13) THEN
    IF x0 = 275 THEN CALL endlogo 'press Enter
    IF x0 = 250 THEN CALL help
    IF x0 = 225 THEN CALL senior
    IF x0 = 200 THEN CALL main
END IF
GOTO pp
CALL endlogo

SUB checkcomputerwin
DO 'check line and row (4 chess) 先竖再横
    count = 0: count1 = 0
    a = a + 1
    b = 0
    DO
        b = b + 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 5 THEN CALL youlose: CALL endlogo
        ELSE
            count = 0
        END IF
        IF xy(b, a, 2) = 2 THEN
            count1 = count1 + 1
            IF count1 = 5 THEN CALL youlose: CALL endlogo
        ELSE
            count1 = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL a = 15

n = 4 'check 斜 4 chess分为四个部分 \\\\\\
DO '                             \\\\\\
    count = 0
    n = n + 1
    a = 0
    b = n + 1
    DO
        b = b - 1
        a = a + 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 5 THEN CALL youlose: CALL endlogo
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

n = 1
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        b = b + 1
        a = a - 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 5 THEN CALL youlose: CALL endlogo
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 0
DO
    count = 0
    n = n + 1
    b = n - 1
    a = 0
    DO
        a = a + 1
        b = b + 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 5 THEN CALL youlose: CALL endlogo
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 6
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        a = a - 1
        b = b - 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 5 THEN CALL youlose: CALL endlogo
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

END SUB

SUB checkmanwin
DO 'check line and row (4 chess)
    count = 0: count1 = 0
    a = a + 1
    b = 0
    DO
        b = b + 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 5 THEN CALL youwin: CALL endlogo
        ELSE
            count = 0
        END IF
        IF xy(b, a, 2) = 1 THEN
            count1 = count1 + 1
            IF count1 = 5 THEN CALL youwin: CALL endlogo
        ELSE
            count1 = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL a = 15

n = 4 'check xie 4 chess
DO
    count = 0
    n = n + 1
    a = 0
    b = n + 1
    DO
        b = b - 1
        a = a + 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 5 THEN CALL youwin: CALL endlogo
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

n = 1
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        b = b + 1
        a = a - 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 5 THEN CALL youwin: CALL endlogo
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 0
DO
    count = 0
    n = n + 1
    b = n - 1
    a = 0
    DO
        a = a + 1
        b = b + 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 5 THEN CALL youwin: CALL endlogo
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 6
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        a = a - 1
        b = b - 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 5 THEN CALL youwin: CALL endlogo
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

END SUB

SUB checkpc3chess
'check line and row (3 chess)
DO
    count = 0: count1 = 0
    a = a + 1
    b = 0
    DO
        b = b + 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 3 THEN
                IF b < 15 AND b - 3 >= 0 THEN
                    IF xy(a, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a, b + 1, 0), xy(a, b + 1, 1)), 13, 15
                        xy(a, b + 1, 2) = 2
                        PAINT (xy(a, b + 1, 0), xy(a, b + 1, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    ELSEIF xy(a, b - 3, 2) = 0 AND b - 3 > 0 THEN
                        CIRCLE (xy(a, b - 3, 0), xy(a, b - 3, 1)), 13, 15
                        xy(a, b - 3, 2) = 2
                        PAINT (xy(a, b - 3, 0), xy(a, b - 3, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    END IF
                ELSEIF b = 15 THEN
                    IF xy(a, b - 3, 2) = 0 THEN
                        CIRCLE (xy(a, b - 3, 0), xy(a, b - 3, 1)), 13, 15
                        xy(a, b - 3, 2) = 2
                        PAINT (xy(a, b - 3, 0), xy(a, b - 3, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF

        IF xy(b, a, 2) = 2 THEN
            count1 = count1 + 1
            IF count1 = 3 THEN
                IF b < 15 AND b - 3 >= 0 THEN
                    IF xy(b + 1, a, 2) = 0 THEN
                        CIRCLE (xy(b + 1, a, 0), xy(b + 1, a, 1)), 13, 15
                        xy(b + 1, a, 2) = 2
                        PAINT (xy(b + 1, a, 0), xy(b + 1, a, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    ELSEIF xy(b - 3, a, 2) = 0 AND b - 3 > 0 THEN
                        CIRCLE (xy(b - 3, a, 0), xy(b - 3, a, 1)), 13, 15
                        xy(b - 3, a, 2) = 2
                        PAINT (xy(b - 3, a, 0), xy(b - 3, a, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    END IF
                ELSEIF b = 15 THEN
                    IF xy(b - 3, a, 2) = 0 THEN
                        CIRCLE (xy(b - 3, a, 0), xy(b - 3, a, 1)), 13, 15
                        xy(b - 3, a, 2) = 2
                        PAINT (xy(b - 3, a, 0), xy(b - 3, a, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    END IF
                END IF
            END IF
        ELSE
            count1 = 0
        END IF
 
    LOOP UNTIL b = 15
LOOP UNTIL a = 15
'check xie 3 chess

n = 4
DO
    count = 0
    n = n + 1
    a = 0
    b = n + 1
    DO
        b = b - 1
        a = a + 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 3 THEN
                IF b > 1 THEN
                    IF xy(a + 1, b - 1, 2) = 0 THEN
                        CIRCLE (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 13, 15
                        xy(a + 1, b - 1, 2) = 2
                        PAINT (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    ELSEIF a - 3 > 0 THEN
                        IF xy(a - 3, b + 3, 2) = 0 THEN
                            CIRCLE (xy(a - 3, b + 3, 0), xy(a - 3, b + 3, 1)), 13, 15
                            xy(a - 3, b + 3, 2) = 2
                            PAINT (xy(a - 3, b + 3, 0), xy(a - 3, b + 3, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                        END IF
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

n = 1
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        b = b + 1
        a = a - 1
        IF xy(a, b, 2) = 2 THEN
            count0 = count0 + 1
            IF count0 = 3 THEN
                IF b < 15 THEN
                    IF xy(a - 1, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 13, 15
                        xy(a - 1, b + 1, 2) = 2
                        PAINT (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    ELSEIF a + 3 < 16 THEN
                        IF xy(a + 3, b - 3, 2) = 0 THEN
                            CIRCLE (xy(a + 3, b - 3, 0), xy(a + 3, b - 3, 1)), 13, 15
                            xy(a + 3, b - 3, 2) = 2
                            PAINT (xy(a + 3, b - 3, 0), xy(a + 3, b - 3, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                        END IF
                    END IF
                END IF
            END IF
        ELSE
            count0 = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 0
DO
    count = 0
    n = n + 1
    b = n - 1
    a = 0
    DO
        a = a + 1
        b = b + 1
        IF xy(a, b, 2) = 2 THEN
            count1 = count1 + 1
            IF count1 = 3 THEN
                IF b + 1 < 16 AND a + 1 < 16 THEN
                    IF xy(a + 1, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 13, 15
                        xy(a + 1, b + 1, 2) = 2
                        PAINT (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    ELSEIF a - 3 > 0 AND b - 3 > 0 THEN
                        IF xy(a - 3, b - 3, 2) = 0 THEN
                            CIRCLE (xy(a - 3, b - 3, 0), xy(a - 3, b - 3, 1)), 13, 15
                            xy(a - 3, b - 3, 2) = 2
                            PAINT (xy(a - 3, b - 3, 0), xy(a - 3, b - 3, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                        END IF
                    END IF
                END IF
            END IF
        ELSE
            count1 = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 6
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        a = a - 1
        b = b - 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 3 THEN
                IF b - 1 > 1 AND a - 1 > 1 THEN
                    IF xy(a - 1, b - 1, 2) = 0 THEN
                        CIRCLE (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 13, 15
                        xy(a - 1, b - 1, 2) = 2
                        PAINT (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                    ELSEIF a + 3 < 16 AND b + 3 < 16 THEN
                        IF xy(a + 3, b + 3, 2) = 0 THEN
                            CIRCLE (xy(a + 3, b + 3, 0), xy(a + 3, b + 3, 1)), 13, 15
                            xy(a + 3, b + 3, 2) = 2
                            PAINT (xy(a + 3, b + 3, 0), xy(a + 3, b + 3, 1)), 15: CALL checkcomputerwin: checkpc3 = 1: GOTO back1
                        END IF
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15
back1:
END SUB

SUB checkpc4chess
DO 'check line and row (4 chess)
    count = 0: count1 = 0
    a = a + 1
    b = 0
    DO
        b = b + 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 4 AND b < 15 THEN
                IF xy(a, b + 1, 2) = 0 THEN
                    CIRCLE (xy(a, b + 1, 0), xy(a, b + 1, 1)), 13, 15
                    xy(a, b + 1, 2) = 2
                    PAINT (xy(a, b + 1, 0), xy(a, b + 1, 1)), 15: CALL youlose: CALL endlogo
                ELSEIF b - 4 > 0 THEN
                    IF xy(a, b - 4, 2) = 0 THEN
                        CIRCLE (xy(a, b - 4, 0), xy(a, b - 4, 1)), 13, 15
                        xy(a, b - 4, 2) = 2
                        PAINT (xy(a, b - 4, 0), xy(a, b - 4, 1)), 15: CALL youlose: CALL endlogo
                    END IF
                END IF
            ELSEIF count = 4 AND b = 15 THEN
                IF xy(a, b - 4, 2) = 0 THEN
                    CIRCLE (xy(a, b - 4, 0), xy(a, b - 4, 1)), 13, 15
                    xy(a, b - 4, 2) = 2
                    PAINT (xy(a, b - 4, 0), xy(a, b - 4, 1)), 15: CALL youlose: CALL endlogo
                END IF
            END IF
        ELSE
            count = 0
        END IF
        IF xy(b, a, 2) = 2 THEN
            count1 = count1 + 1
            IF count1 = 4 AND b < 15 THEN
                IF xy(b + 1, a, 2) = 0 THEN
                    CIRCLE (xy(b + 1, a, 0), xy(b + 1, a, 1)), 13, 15
                    xy(b + 1, a, 2) = 2
                    PAINT (xy(b + 1, a, 0), xy(b + 1, a, 1)), 15: CALL youlose: CALL endlogo
                ELSEIF b - 4 > 0 THEN
                    IF xy(b - 4, a, 2) = 0 THEN
                        CIRCLE (xy(b - 4, a, 0), xy(b - 4, a, 1)), 13, 15
                        xy(b - 4, a, 2) = 2
                        PAINT (xy(b - 4, a, 0), xy(b - 4, a, 1)), 15: CALL youlose: CALL endlogo
                    END IF
                END IF
            ELSEIF count1 = 4 AND b = 15 THEN
                IF xy(b - 4, a, 2) = 0 THEN
                    CIRCLE (xy(b - 4, a, 0), xy(b - 4, a, 1)), 13, 15
                    xy(b - 4, a, 2) = 2
                    PAINT (xy(b - 4, a, 0), xy(b - 4, a, 1)), 15: CALL youlose: CALL endlogo
                END IF
            END IF
        ELSE
            count1 = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL a = 15
n = 4 'check xie 4 chess
DO
    count = 0
    n = n + 1
    a = 0
    b = n + 1
    DO
        b = b - 1
        a = a + 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 4 THEN
                IF b > 1 THEN
                    IF xy(a + 1, b - 1, 2) = 0 THEN
                        CIRCLE (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 13, 15
                        xy(a + 1, b - 1, 2) = 2
                        PAINT (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 15: CALL youlose: CALL endlogo
                    ELSEIF a - 4 > 0 THEN
                        IF xy(a - 4, b + 4, 2) = 0 THEN
                            CIRCLE (xy(a - 4, b + 4, 0), xy(a - 4, b + 4, 1)), 13, 15
                            xy(a - 4, b + 4, 2) = 2
                            PAINT (xy(a - 4, b + 4, 0), xy(a - 4, b + 4, 1)), 15: CALL youlose: CALL endlogo
                        END IF
                    END IF
                ELSEIF b = 1 THEN
                    IF xy(a - 4, b + 4, 2) = 0 THEN
                        CIRCLE (xy(a - 4, b + 4, 0), xy(a - 4, b + 4, 1)), 13, 15
                        xy(a - 4, b + 4, 2) = 2
                        PAINT (xy(a - 4, b + 4, 0), xy(a - 4, b + 4, 1)), 15: CALL youlose: CALL endlogo
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

n = 1
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        b = b + 1
        a = a - 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 4 THEN
                IF b < 15 THEN
                    IF xy(a - 1, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 13, 15
                        xy(a - 1, b + 1, 2) = 2
                        PAINT (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 15: CALL youlose: CALL endlogo
                    ELSEIF a + 4 < 16 THEN
                        IF xy(a + 4, b - 4, 2) = 0 THEN
                            CIRCLE (xy(a + 4, b - 4, 0), xy(a + 4, b - 4, 1)), 13, 15
                            xy(a + 4, b - 4, 2) = 2
                            PAINT (xy(a + 4, b - 4, 0), xy(a + 4, b - 4, 1)), 15: CALL youlose: CALL endlogo
                        END IF
                    END IF
                ELSEIF b = 15 THEN
                    IF xy(a + 4, b - 4, 2) = 0 THEN
                        CIRCLE (xy(a + 4, b - 4, 0), xy(a + 4, b - 4, 1)), 13, 15
                        xy(a + 4, b - 4, 2) = 2
                        PAINT (xy(a + 4, b - 4, 0), xy(a + 4, b - 4, 1)), 15: CALL youlose: CALL endlogo
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 0
DO
    count = 0
    n = n + 1
    b = n - 1
    a = 0
    DO
        a = a + 1
        b = b + 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 4 THEN
                IF b + 1 < 16 AND a + 1 < 16 THEN
                    IF xy(a + 1, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 13, 15
                        xy(a + 1, b + 1, 2) = 2
                        PAINT (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 15: CALL youlose: CALL endlogo
                    ELSEIF a - 4 > 0 AND b - 4 > 0 THEN
                        IF xy(a - 4, b - 4, 2) = 0 THEN
                            CIRCLE (xy(a - 4, b - 4, 0), xy(a - 4, b - 4, 1)), 13, 15
                            xy(a - 4, b - 4, 2) = 2
                            PAINT (xy(a - 4, b - 4, 0), xy(a - 4, b - 4, 1)), 15: CALL youlose: CALL endlogo
                        END IF
                    END IF
                ELSEIF b = 15 THEN
                    IF xy(a - 4, b - 4, 2) = 0 THEN
                        CIRCLE (xy(a - 4, b - 4, 0), xy(a - 4, b - 4, 1)), 13, 15
                        xy(a - 4, b - 4, 2) = 2
                        PAINT (xy(a - 4, b - 4, 0), xy(a - 4, b - 4, 1)), 15: CALL youlose: CALL endlogo
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 6
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        a = a - 1
        b = b - 1
        IF xy(a, b, 2) = 2 THEN
            count = count + 1
            IF count = 4 THEN
                IF b - 1 > 1 AND a - 1 > 1 THEN
                    IF xy(a - 1, b - 1, 2) = 0 THEN
                        CIRCLE (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 13, 15
                        xy(a - 1, b - 1, 2) = 2
                        PAINT (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 15: CALL youlose: CALL endlogo
                    ELSEIF a + 4 < 16 AND b + 4 < 16 THEN
                        IF xy(a + 4, b + 4, 2) = 0 THEN
                            CIRCLE (xy(a + 4, b + 4, 0), xy(a + 4, b + 4, 1)), 13, 15
                            xy(a + 4, b + 4, 2) = 2
                            PAINT (xy(a + 4, b + 4, 0), xy(a + 4, b + 4, 1)), 15: CALL youlose: CALL endlogo
                        END IF
                    END IF
                ELSEIF b = 1 THEN
                    IF xy(a + 4, b + 4, 2) = 0 THEN
                        CIRCLE (xy(a + 4, b + 4, 0), xy(a + 4, b + 4, 1)), 13, 15
                        xy(a + 4, b + 4, 2) = 2
                        PAINT (xy(a + 4, b + 4, 0), xy(a + 4, b + 4, 1)), 15: CALL youlose: CALL endlogo
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15


END SUB

SUB endlogo
CLS
FOR c% = 480 TO 200 STEP -1
    CALL hzk24(200, c% + 1, 0, "程序设计")
    CALL hzk24(360, c% + 1, 0, "程晨")
    CALL hzk24(200, c%, 10, "程序设计")
    CALL hzk24(360, c%, 10, "程晨")
    Delay (0.002)
NEXT c%
40 a$ = INKEY$: IF a$ = "" THEN 40
END
END SUB

SUB Delay (time)
time = time + TIMER
WHILE TIMER < time
WEND
END SUB


SUB help
LINE (257, 237)-(455, 290), 9, BF
CALL hzk24(260, 240, 0, "程仔风云精彩无限")
CALL hzk24(260, 265, 0, "版权所有违者必究")
20 a$ = INKEY$: IF a$ = "" THEN 20
CLS
LINE (190, 195)-(255, 300), 9, BF
LINE (192, 197)-(253, 298), 0, B
END SUB

SUB hzk24 (x%, y%, colo!, word$)
OPEN "b", #2, "chinease.ci"
ln$ = SPACE$(72): qwm$ = word$
FOR l = 1 TO LEN(qwm$) STEP 2
    lq = ASC(MID$(qwm$, l, 1)) - 160
    lw = ASC(MID$(qwm$, l + 1, 1)) - 160
    add& = ((lq - 16) * 94 + lw - 1) * 72& + 1
    GET #2, add&, ln$
    FOR j = 1 TO 72 STEP 3
        d& = ASC(MID$(ln$, j, 1))
        d& = d& * 256 + ASC(MID$(ln$, j + 1, 1))
        IF d& > 32767 THEN d& = d& - 65536
        LINE (x%, y%)-STEP(0, 15), colo!, , d&
        d& = ASC(MID$(ln$, j + 2, 1))
        d& = d& + VAL("&h" + HEX$(d&) + "00")
        LINE -STEP(0, 7), colo!, , d&
        x% = x% + 1
    NEXT
NEXT
CLOSE #2
END SUB

SUB junior
CALL checkmanwin
CALL checkpc4chess
check3 = 0
DO 'check line and row (4 chess)
    count = 0: count1 = 0
    a = a + 1
    b = 0
    DO
        b = b + 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 4 AND b < 15 THEN
                IF xy(a, b + 1, 2) = 0 THEN
                    CIRCLE (xy(a, b + 1, 0), xy(a, b + 1, 1)), 13, 15
                    xy(a, b + 1, 2) = 2
                    PAINT (xy(a, b + 1, 0), xy(a, b + 1, 1)), 15: CALL checkcomputerwin: GOTO back
                ELSEIF b - 4 > 0 THEN
                    IF xy(a, b - 4, 2) = 0 THEN
                        CIRCLE (xy(a, b - 4, 0), xy(a, b - 4, 1)), 13, 15
                        xy(a, b - 4, 2) = 2
                        PAINT (xy(a, b - 4, 0), xy(a, b - 4, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                END IF
            ELSEIF count = 4 AND b = 15 THEN
                IF xy(a, b - 4, 2) = 0 THEN
                    CIRCLE (xy(a, b - 4, 0), xy(a, b - 4, 1)), 13, 15
                    xy(a, b - 4, 2) = 2
                    PAINT (xy(a, b - 4, 0), xy(a, b - 4, 1)), 15: CALL checkcomputerwin: GOTO back
                END IF
            END IF
        ELSE
            count = 0
        END IF
        IF xy(b, a, 2) = 1 THEN
            count1 = count1 + 1
            IF count1 = 4 AND b < 15 THEN
                IF xy(b + 1, a, 2) = 0 THEN
                    CIRCLE (xy(b + 1, a, 0), xy(b + 1, a, 1)), 13, 15
                    xy(b + 1, a, 2) = 2
                    PAINT (xy(b + 1, a, 0), xy(b + 1, a, 1)), 15: CALL checkcomputerwin: GOTO back
                ELSEIF b - 4 > 0 THEN
                    IF xy(b - 4, a, 2) = 0 THEN
                        CIRCLE (xy(b - 4, a, 0), xy(b - 4, a, 1)), 13, 15
                        xy(b - 4, a, 2) = 2
                        PAINT (xy(b - 4, a, 0), xy(b - 4, a, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                END IF
            ELSEIF count1 = 4 AND b = 15 THEN
                IF xy(b - 4, a, 2) = 0 THEN
                    CIRCLE (xy(b - 4, a, 0), xy(b - 4, a, 1)), 13, 15
                    xy(b - 4, a, 2) = 2
                    PAINT (xy(b - 4, a, 0), xy(b - 4, a, 1)), 15: CALL checkcomputerwin: GOTO back
                END IF
            END IF
        ELSE
            count1 = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL a = 15

n = 4 'check xie 4 chess
DO
    count = 0
    n = n + 1
    a = 0
    b = n + 1
    DO
        b = b - 1
        a = a + 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 4 THEN
                IF b > 1 THEN
                    IF xy(a + 1, b - 1, 2) = 0 THEN
                        CIRCLE (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 13, 15
                        xy(a + 1, b - 1, 2) = 2
                        PAINT (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF a - 4 > 0 THEN
                        IF xy(a - 4, b + 4, 2) = 0 THEN
                            CIRCLE (xy(a - 4, b + 4, 0), xy(a - 4, b + 4, 1)), 13, 15
                            xy(a - 4, b + 4, 2) = 2
                            PAINT (xy(a - 4, b + 4, 0), xy(a - 4, b + 4, 1)), 15: CALL checkcomputerwin: GOTO back
                        END IF
                    END IF
                ELSEIF b = 1 THEN
                    IF xy(a - 4, b + 4, 2) = 0 THEN
                        CIRCLE (xy(a - 4, b + 4, 0), xy(a - 4, b + 4, 1)), 13, 15
                        xy(a - 4, b + 4, 2) = 2
                        PAINT (xy(a - 4, b + 4, 0), xy(a - 4, b + 4, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

n = 1
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        b = b + 1
        a = a - 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 4 THEN
                IF b < 15 THEN
                    IF xy(a - 1, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 13, 15
                        xy(a - 1, b + 1, 2) = 2
                        PAINT (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF a + 4 < 16 THEN
                        IF xy(a + 4, b - 4, 2) = 0 THEN
                            CIRCLE (xy(a + 4, b - 4, 0), xy(a + 4, b - 4, 1)), 13, 15
                            xy(a + 4, b - 4, 2) = 2
                            PAINT (xy(a + 4, b - 4, 0), xy(a + 4, b - 4, 1)), 15: CALL checkcomputerwin: GOTO back
                        END IF
                    END IF
                ELSEIF b = 15 THEN
                    IF xy(a + 4, b - 4, 2) = 0 THEN
                        CIRCLE (xy(a + 4, b - 4, 0), xy(a + 4, b - 4, 1)), 13, 15
                        xy(a + 4, b - 4, 2) = 2
                        PAINT (xy(a + 4, b - 4, 0), xy(a + 4, b - 4, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 0
DO
    count = 0
    n = n + 1
    b = n - 1
    a = 0
    DO
        a = a + 1
        b = b + 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 4 THEN
                IF b + 1 < 16 AND a + 1 < 16 THEN
                    IF xy(a + 1, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 13, 15
                        xy(a + 1, b + 1, 2) = 2
                        PAINT (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF a - 4 > 0 AND b - 4 > 0 THEN
                        IF xy(a - 4, b - 4, 2) = 0 THEN
                            CIRCLE (xy(a - 4, b - 4, 0), xy(a - 4, b - 4, 1)), 13, 15
                            xy(a - 4, b - 4, 2) = 2
                            PAINT (xy(a - 4, b - 4, 0), xy(a - 4, b - 4, 1)), 15: CALL checkcomputerwin: GOTO back
                        END IF
                    END IF
                ELSEIF b = 15 THEN
                    IF xy(a - 4, b - 4, 2) = 0 THEN
                        CIRCLE (xy(a - 4, b - 4, 0), xy(a - 4, b - 4, 1)), 13, 15
                        xy(a - 4, b - 4, 2) = 2
                        PAINT (xy(a - 4, b - 4, 0), xy(a - 4, b - 4, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 6
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        a = a - 1
        b = b - 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 4 THEN
                IF b - 1 > 1 AND a - 1 > 1 THEN
                    IF xy(a - 1, b - 1, 2) = 0 THEN
                        CIRCLE (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 13, 15
                        xy(a - 1, b - 1, 2) = 2
                        PAINT (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF a + 4 < 16 AND b + 4 < 16 THEN
                        IF xy(a + 4, b + 4, 2) = 0 THEN
                            CIRCLE (xy(a + 4, b + 4, 0), xy(a + 4, b + 4, 1)), 13, 15
                            xy(a + 4, b + 4, 2) = 2
                            PAINT (xy(a + 4, b + 4, 0), xy(a + 4, b + 4, 1)), 15: CALL checkcomputerwin: GOTO back
                        END IF
                    END IF
                ELSEIF b = 1 THEN
                    IF xy(a + 4, b + 4, 2) = 0 THEN
                        CIRCLE (xy(a + 4, b + 4, 0), xy(a + 4, b + 4, 1)), 13, 15
                        xy(a + 4, b + 4, 2) = 2
                        PAINT (xy(a + 4, b + 4, 0), xy(a + 4, b + 4, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

CALL checkpc3chess
IF checkpc3 = 1 THEN checkpc3 = 0: GOTO back
'check line and row (3 chess)
a = 0: b = 0
DO
    count = 0: count1 = 0
    a = a + 1
    b = 0
    DO
        b = b + 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 3 THEN
                IF b < 15 AND b - 3 >= 0 THEN
                    IF xy(a, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a, b + 1, 0), xy(a, b + 1, 1)), 13, 15
                        xy(a, b + 1, 2) = 2
                        PAINT (xy(a, b + 1, 0), xy(a, b + 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF xy(a, b - 3, 2) = 0 AND b - 3 > 0 THEN
                        CIRCLE (xy(a, b - 3, 0), xy(a, b - 3, 1)), 13, 15
                        xy(a, b - 3, 2) = 2
                        PAINT (xy(a, b - 3, 0), xy(a, b - 3, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                ELSEIF b = 15 THEN
                    IF xy(a, b - 3, 2) = 0 THEN
                        CIRCLE (xy(a, b - 3, 0), xy(a, b - 3, 1)), 13, 15
                        xy(a, b - 3, 2) = 2
                        PAINT (xy(a, b - 3, 0), xy(a, b - 3, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
 
        IF xy(b, a, 2) = 1 THEN
            count1 = count1 + 1
            IF count1 = 3 THEN
                IF b < 15 AND b - 3 >= 0 THEN
                    IF xy(b + 1, a, 2) = 0 THEN
                        CIRCLE (xy(b + 1, a, 0), xy(b + 1, a, 1)), 13, 15
                        xy(b + 1, a, 2) = 2
                        PAINT (xy(b + 1, a, 0), xy(b + 1, a, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF xy(b - 3, a, 2) = 0 AND b - 3 > 0 THEN
                        CIRCLE (xy(b - 3, a, 0), xy(b - 3, a, 1)), 13, 15
                        xy(b - 3, a, 2) = 2
                        PAINT (xy(b - 3, a, 0), xy(b - 3, a, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                ELSEIF b = 15 THEN
                    IF xy(b - 3, a, 2) = 0 THEN
                        CIRCLE (xy(b - 3, a, 0), xy(b - 3, a, 1)), 13, 15
                        xy(b - 3, a, 2) = 2
                        PAINT (xy(b - 3, a, 0), xy(b - 3, a, 1)), 15: CALL checkcomputerwin: GOTO back
                    END IF
                END IF
            END IF
        ELSE
            count1 = 0
        END IF
  
    LOOP UNTIL b = 15
LOOP UNTIL a = 15
'check xie 3 chess

n = 4
DO
    count = 0
    n = n + 1
    a = 0
    b = n + 1
    DO
        b = b - 1
        a = a + 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 3 THEN
                IF b > 1 THEN
                    IF xy(a + 1, b - 1, 2) = 0 THEN
                        CIRCLE (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 13, 15
                        xy(a + 1, b - 1, 2) = 2
                        PAINT (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF a - 3 > 0 THEN
                        IF xy(a - 3, b + 3, 2) = 0 THEN
                            CIRCLE (xy(a - 3, b + 3, 0), xy(a - 3, b + 3, 1)), 13, 15
                            xy(a - 3, b + 3, 2) = 2
                            PAINT (xy(a - 3, b + 3, 0), xy(a - 3, b + 3, 1)), 15: CALL checkcomputerwin: GOTO back
                        END IF
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 15

n = 1
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        b = b + 1
        a = a - 1
        IF xy(a, b, 2) = 1 THEN
            count0 = count0 + 1
            IF count0 = 3 THEN
                IF b < 15 THEN
                    IF xy(a - 1, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 13, 15
                        xy(a - 1, b + 1, 2) = 2
                        PAINT (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF a + 3 < 16 THEN
                        IF xy(a + 3, b - 3, 2) = 0 THEN
                            CIRCLE (xy(a + 3, b - 3, 0), xy(a + 3, b - 3, 1)), 13, 15
                            xy(a + 3, b - 3, 2) = 2
                            PAINT (xy(a + 3, b - 3, 0), xy(a + 3, b - 3, 1)), 15: CALL checkcomputerwin: GOTO back
                        END IF
                    END IF
                END IF
            END IF
        ELSE
            count0 = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 0
DO
    count = 0
    n = n + 1
    b = n - 1
    a = 0
    DO
        a = a + 1
        b = b + 1
        IF xy(a, b, 2) = 1 THEN
            count1 = count1 + 1
            IF count1 = 3 THEN
                IF b + 1 < 16 AND a + 1 < 16 THEN
                    IF xy(a + 1, b + 1, 2) = 0 THEN
                        CIRCLE (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 13, 15
                        xy(a + 1, b + 1, 2) = 2
                        PAINT (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF a - 3 > 0 AND b - 3 > 0 THEN
                        IF xy(a - 3, b - 3, 2) = 0 THEN
                            CIRCLE (xy(a - 3, b - 3, 0), xy(a - 3, b - 3, 1)), 13, 15
                            xy(a - 3, b - 3, 2) = 2
                            PAINT (xy(a - 3, b - 3, 0), xy(a - 3, b - 3, 1)), 15: CALL checkcomputerwin: GOTO back
                        END IF
                    END IF
                END IF
            END IF
        ELSE
            count1 = 0
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL n = 11

n = 6
DO
    count = 0
    a = 16
    n = n + 1
    b = n - 1
    DO
        a = a - 1
        b = b - 1
        IF xy(a, b, 2) = 1 THEN
            count = count + 1
            IF count = 3 THEN
                IF b - 1 > 1 AND a - 1 > 1 THEN
                    IF xy(a - 1, b - 1, 2) = 0 THEN
                        CIRCLE (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 13, 15
                        xy(a - 1, b - 1, 2) = 2
                        PAINT (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 15: CALL checkcomputerwin: GOTO back
                    ELSEIF a + 3 < 16 AND b + 3 < 16 THEN
                        IF xy(a + 3, b + 3, 2) = 0 THEN
                            CIRCLE (xy(a + 3, b + 3, 0), xy(a + 3, b + 3, 1)), 13, 15
                            xy(a + 3, b + 3, 2) = 2
                            PAINT (xy(a + 3, b + 3, 0), xy(a + 3, b + 3, 1)), 15: CALL checkcomputerwin: GOTO back
                        END IF
                    END IF
                END IF
            END IF
        ELSE
            count = 0
        END IF
    LOOP UNTIL b = 1
LOOP UNTIL n = 16

'对方两个子之间有空就填
IF x00 > 2 AND x00 < 14 AND y00 > 2 AND y00 < 14 THEN 'wei pan duan wan
    IF xy(x00 - 1, y00, 2) = 0 AND xy(x00 - 2, y00, 2) = 1 THEN
        CIRCLE (xy(x00 - 1, y00, 0), xy(x00 - 1, y00, 1)), 13, 15
        xy(x00 - 1, y00, 2) = 2
        PAINT (xy(x00 - 1, y00, 0), xy(x00 - 1, y00, 1)), 15: CALL checkcomputerwin: GOTO back
    END IF
    IF xy(x00 + 1, y00, 2) = 0 AND xy(x00 + 2, y00, 2) = 1 THEN
        CIRCLE (xy(x00 + 1, y00, 0), xy(x00 + 1, y00, 1)), 13, 15
        xy(x00 + 1, y00, 2) = 2
        PAINT (xy(x00 + 1, y00, 0), xy(x00 + 1, y00, 1)), 15: CALL checkcomputerwin: GOTO back
    END IF
    IF xy(x00, y00 + 1, 2) = 0 AND xy(x00, y00 + 2, 2) = 1 THEN
        CIRCLE (xy(x00, y00 + 1, 0), xy(x00, y00 + 1, 1)), 13, 15
        xy(x00, y00 + 1, 2) = 2
        PAINT (xy(x00, y00 + 1, 0), xy(x00, y00 + 1, 1)), 15: CALL checkcomputerwin: GOTO back
    END IF
    IF xy(x00, y00 - 1, 2) = 0 AND xy(x00, y00 - 2, 2) = 1 THEN
        CIRCLE (xy(x00, y00 - 1, 0), xy(x00, y00 - 1, 1)), 13, 15
        xy(x00, y00 - 1, 2) = 2
        PAINT (xy(x00, y00 - 1, 0), xy(x00, y00 - 1, 1)), 15: CALL checkcomputerwin: GOTO back
    END IF
    IF xy(x00 + 1, y00 + 1, 2) = 0 AND xy(x00 + 2, y00 + 2, 2) = 1 THEN
        CIRCLE (xy(x00 + 1, y00 + 1, 0), xy(x00 + 1, y00 + 1, 1)), 13, 15
        xy(x00 + 1, y00 + 1, 2) = 2
        PAINT (xy(x00 + 1, y00 + 1, 0), xy(x00 + 1, y00 + 1, 1)), 15: CALL checkcomputerwin: GOTO back
    END IF
    IF xy(x00 - 1, y00 - 1, 2) = 0 AND xy(x00 - 2, y00 - 2, 2) = 1 THEN
        CIRCLE (xy(x00 - 1, y00 - 1, 0), xy(x00 - 1, y00 - 1, 1)), 13, 15
        xy(x00 - 1, y00 - 1, 2) = 2
        PAINT (xy(x00 - 1, y00 - 1, 0), xy(x00 - 1, y00 - 1, 1)), 15: CALL checkcomputerwin: GOTO back
    END IF
    IF xy(x00 + 1, y00 - 1, 2) = 0 AND xy(x00 + 2, y00 - 2, 2) = 1 THEN
        CIRCLE (xy(x00 + 1, y00 - 1, 0), xy(x00 + 1, y00 - 1, 1)), 13, 15
        xy(x00 + 1, y00 - 1, 2) = 2
        PAINT (xy(x00 + 1, y00 - 1, 0), xy(x00 + 1, y00 - 1, 1)), 15: CALL checkcomputerwin: GOTO back
    END IF
    IF xy(x00 - 1, y00 + 1, 2) = 0 AND xy(x00 - 2, y00 + 2, 2) = 1 THEN
        CIRCLE (xy(x00 - 1, y00 + 1, 0), xy(x00 - 1, y00 + 1, 1)), 13, 15
        xy(x00 - 1, y00 + 1, 2) = 2
        PAINT (xy(x00 - 1, y00 + 1, 0), xy(x00 - 1, y00 + 1, 1)), 15: CALL checkcomputerwin: GOTO back
    END IF
END IF

CALL pccheck2chess
IF check3 = 1 THEN GOTO back
CALL pccheck1chess
IF check3 = 1 THEN GOTO back

RANDOMIZE TIMER

getxy:
DO
    a = INT(16 * RND): b = INT(16 * RND)
LOOP UNTIL xy(a, b, 2) = 1 AND a > 0 AND b > 0
IF a + 1 < 15 AND a - 1 > 1 AND b + 1 < 15 AND b - 1 > 1 THEN
    IF xy(a + 1, b, 2) = 0 THEN
        x = a + 1: y = b
    ELSEIF xy(a - 1, b, 2) = 0 THEN
        x = a - 1: y = b
    ELSEIF xy(a, b + 1, 2) = 0 THEN
        x = a: y = b + 1
    ELSEIF xy(a, b - 1, 2) = 0 THEN
        x = a: y = b - 1
    ELSEIF xy(a + 1, b + 1, 2) = 0 THEN
        x = a + 1: y = b + 1
    ELSEIF xy(a + 1, b - 1, 2) = 0 THEN
        x = a + 1: y = b - 1
    ELSEIF xy(a - 1, b + 1, 2) = 0 THEN
        x = a - 1: y = b + 1
    ELSEIF xy(a - 1, b - 1, 2) = 0 THEN
        x = a - 1: y = n - 1
    END IF
ELSE
    DO
        x = INT(16 * RND): y = INT(16 * RND)
    LOOP UNTIL x > 1 AND y > 1 AND xy(x, y, 2) = 0
END IF
IF x = 0 AND y = 0 THEN GOTO getxy '一定要取到x,y的值


'这断代码好象是多余的，但为了稳定性还是加上去
'******************************************
IF x <> 0 AND y <> 0 THEN
    CIRCLE (xy(x, y, 0), xy(x, y, 1)), 13, 15
    xy(x, y, 2) = 2
    PAINT (xy(x, y, 0), xy(x, y, 1)), 15
ELSEIF x = 0 AND y = 0 THEN
    DO
        x = INT(16 * RND): y = INT(16 * RND)
    LOOP UNTIL x > 1 AND y > 1 AND xy(x, y, 2) = 0
    CIRCLE (xy(x, y, 0), xy(x, y, 1)), 13, 15
    xy(x, y, 2) = 2
    PAINT (xy(x, y, 0), xy(x, y, 1)), 15
END IF
'******************************************
back:
END SUB

SUB logo
CLS
CALL hzk24(251, 201, 12, "五子风云")
CALL hzk24(250, 200, 14, "五子风云")
OPEN "ciciweb.ci" FOR INPUT AS #1
COLOR 10
DO
    INPUT #1, x, y
    PSET (y + 255, x + 225)
LOOP UNTIL EOF(1)
CLOSE #1
15 a$ = INKEY$: IF a$ = "" THEN 15
END SUB

SUB main
CLS
LINE (104, 10)-(540, 444), 6, BF
LINE (106, 12)-(538, 442), 10, B
FOR a = 17 TO 440 STEP 30 '画五子棋盘
    LINE (112, a)-(532, a), 10, B
NEXT a
FOR a = 112 TO 540 STEP 30
    LINE (a, 17)-(a, 436), 10, B
NEXT a
x = 322: y = 227
move:
DO
    a$ = INKEY$
    a$ = RIGHT$(a$, 1)
LOOP UNTIL a$ = "H" OR a$ = "P" OR a$ = "K" OR a$ = "M" OR a$ = CHR$(27) OR a$ = CHR$(13)
CIRCLE (x, y), 14, 6 'clear screen
PSET (x + 14, y), 10
PSET (x - 14, y), 10
PSET (x, y + 14), 10
PSET (x, y - 14), 10
IF x = 112 THEN PSET (106, y - 13), 10: PSET (106, y + 13), 10
IF x = 532 THEN PSET (538, y - 13), 10: PSET (538, y + 13), 10
IF y = 17 THEN PSET (x - 13, 12), 10: PSET (x + 13, 12), 10
IF y = 437 THEN PSET (x - 13, 442), 10: PSET (x + 13, 442), 10
LINE (98, 4)-(103, 451), 0, BF
LINE (98, 3)-(541, 9), 0, BF
LINE (541, 4)-(546, 451), 0, BF
LINE (98, 445)-(546, 451), 0, BF
SELECT CASE a$
    CASE "H"
        y = y - 30
    CASE "P"
        y = y + 30
    CASE "K"
        x = x - 30
    CASE "M"
        x = x + 30
    CASE CHR$(27)
        CALL endlogo
    CASE CHR$(13)
        n = 0
        WHILE x2 >= 0 '把复杂的坐标转化为三维数组相对简单的坐标
            n = n + 1
            x2 = x - 82 - 30 * n
        WEND
        x2 = n - 1
        n = 0
        WHILE y2 >= 0
            n = n + 1
            y2 = y + 17 - 30 * n
        WEND
        y2 = n - 1
        IF xy(x2, y2, 2) = 0 THEN
            CIRCLE (x, y), 13, 0
            PAINT (x, y), 0
            xy(x2, y2, 2) = 1
            x00 = x2: y00 = y2
            CALL junior
  
        END IF
END SELECT
IF x < 112 THEN x = 112 'move by contrl
IF x > 532 THEN x = 532
IF y < 17 THEN y = 17
IF y > 437 THEN y = 437
CIRCLE (x, y), 14, 1 'move circle
GOTO move

END SUB

SUB pccheck1chess
DO '检测自己两子有空的地方
    a = a + 1
    b = 0
    DO
        b = b + 1
        IF a > 2 AND a < 14 AND b > 2 AND b < 14 THEN
            IF xy(a, b, 2) = 1 THEN
                IF xy(a - 1, b, 2) = 0 AND xy(a - 2, b, 2) = 1 THEN
                    CIRCLE (xy(a - 1, b, 0), xy(a - 1, b, 1)), 13, 15
                    xy(a - 1, b, 2) = 2
                    PAINT (xy(a - 1, b, 0), xy(a - 1, b, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back3
                END IF
                IF xy(a + 1, b, 2) = 0 AND xy(a + 2, b, 2) = 1 THEN
                    CIRCLE (xy(a + 1, b, 0), xy(a + 1, b, 1)), 13, 15
                    xy(a + 1, b, 2) = 2
                    PAINT (xy(a + 1, b, 0), xy(a + 1, b, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back3
                END IF
                IF xy(a, b + 1, 2) = 0 AND xy(a, b + 2, 2) = 1 THEN
                    CIRCLE (xy(a, b + 1, 0), xy(a, b + 1, 1)), 13, 15
                    xy(a, b + 1, 2) = 2
                    PAINT (xy(a, b + 1, 0), xy(a, b + 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back3
                END IF
                IF xy(a, b - 1, 2) = 0 AND xy(a, b - 2, 2) = 1 THEN
                    CIRCLE (xy(a, b - 1, 0), xy(a, b - 1, 1)), 13, 15
                    xy(a, b - 1, 2) = 2
                    PAINT (xy(a, b - 1, 0), xy(a, b - 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back3
                END IF
                IF xy(a + 1, b + 1, 2) = 0 AND xy(a + 2, b + 2, 2) = 1 THEN
                    CIRCLE (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 13, 15
                    xy(a + 1, b + 1, 2) = 2
                    PAINT (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back3
                END IF
                IF xy(a - 1, b - 1, 2) = 0 AND xy(a - 2, b - 2, 2) = 1 THEN
                    CIRCLE (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 13, 15
                    xy(a - 1, b - 1, 2) = 2
                    PAINT (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back3
                END IF
                IF xy(a + 1, b - 1, 2) = 0 AND xy(a + 2, b - 2, 2) = 1 THEN
                    CIRCLE (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 13, 15
                    xy(a + 1, b - 1, 2) = 2
                    PAINT (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back3
                END IF
                IF xy(a - 1, b + 1, 2) = 0 AND xy(a - 2, b + 2, 2) = 1 THEN
                    CIRCLE (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 13, 15
                    xy(a - 1, b + 1, 2) = 2
                    PAINT (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back3
                END IF
            END IF
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL a = 15
back3:

END SUB

SUB pccheck2chess
DO '检测黑子两子有空的地方
    a = a + 1
    b = 0
    DO
        b = b + 1
        IF a > 2 AND a < 14 AND b > 2 AND b < 14 THEN
            IF xy(a, b, 2) = 2 THEN
                IF xy(a - 1, b, 2) = 0 AND xy(a - 2, b, 2) = 2 THEN
                    CIRCLE (xy(a - 1, b, 0), xy(a - 1, b, 1)), 13, 15
                    xy(a - 1, b, 2) = 2
                    PAINT (xy(a - 1, b, 0), xy(a - 1, b, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back2
                END IF
                IF xy(a + 1, b, 2) = 0 AND xy(a + 2, b, 2) = 2 THEN
                    CIRCLE (xy(a + 1, b, 0), xy(a + 1, b, 1)), 13, 15
                    xy(a + 1, b, 2) = 2
                    PAINT (xy(a + 1, b, 0), xy(a + 1, b, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back2
                END IF
                IF xy(a, b + 1, 2) = 0 AND xy(a, b + 2, 2) = 2 THEN
                    CIRCLE (xy(a, b + 1, 0), xy(a, b + 1, 1)), 13, 15
                    xy(a, b + 1, 2) = 2
                    PAINT (xy(a, b + 1, 0), xy(a, b + 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back2
                END IF
                IF xy(a, b - 1, 2) = 0 AND xy(a, b - 2, 2) = 2 THEN
                    CIRCLE (xy(a, b - 1, 0), xy(a, b - 1, 1)), 13, 15
                    xy(a, b - 1, 2) = 2
                    PAINT (xy(a, b - 1, 0), xy(a, b - 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back2
                END IF
                IF xy(a + 1, b + 1, 2) = 0 AND xy(a + 2, b + 2, 2) = 2 THEN
                    CIRCLE (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 13, 15
                    xy(a + 1, b + 1, 2) = 2
                    PAINT (xy(a + 1, b + 1, 0), xy(a + 1, b + 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back2
                END IF
                IF xy(a - 1, b - 1, 2) = 0 AND xy(a - 2, b - 2, 2) = 2 THEN
                    CIRCLE (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 13, 15
                    xy(a - 1, b - 1, 2) = 2
                    PAINT (xy(a - 1, b - 1, 0), xy(a - 1, b - 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back2
                END IF
                IF xy(a + 1, b - 1, 2) = 0 AND xy(a + 2, b - 2, 2) = 2 THEN
                    CIRCLE (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 13, 15
                    xy(a + 1, b - 1, 2) = 2
                    PAINT (xy(a + 1, b - 1, 0), xy(a + 1, b - 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back2
                END IF
                IF xy(a - 1, b + 1, 2) = 0 AND xy(a - 2, b + 2, 2) = 2 THEN
                    CIRCLE (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 13, 15
                    xy(a - 1, b + 1, 2) = 2
                    PAINT (xy(a - 1, b + 1, 0), xy(a - 1, b + 1, 1)), 15: check3 = 1: CALL checkcomputerwin: GOTO back2
                END IF
            END IF
        END IF
    LOOP UNTIL b = 15
LOOP UNTIL a = 15
back2:
END SUB

SUB senior
COLOR 14
x1 = 262: y1 = 232 '真实坐标
LINE (260, 225)-(350, 245), 9, BF
LINE (262, 227)-(348, 243), 0, B
CALL hzk24(50, 410, 14, "请输入密码")
CALL hzk24(50, 435, 14, "打败初级后会得到密码")
FOR n = 1 TO 8
    11 a$ = INKEY$: IF a$ = "" THEN 11
    b$ = b$ + a$
    OPEN "star.ci" FOR INPUT AS #1
    DO
        INPUT #1, x, y
        PSET (x + x1, y + y1)
    LOOP UNTIL EOF(1)
    CLOSE #1
    x1 = x1 + 10 '坐标转换,其它地方不需要
NEXT n
IF b$ = "cici1234" OR b$ = "CICI1234" THEN
    LINE (50, 410)-(350, 455), 0, BF '清屏功能
    CALL hzk24(50, 410, 14, "本版没有高级功能")
    CALL hzk24(50, 435, 14, "请到程仔风云网下载最新版本")
    OPEN "ciciweb.ci" FOR INPUT AS #1
    x2 = 380: y2 = 440
    DO
        INPUT #1, x, y
        PSET (y + x2, x + y2)
    LOOP UNTIL EOF(1)
    CLOSE #1
END IF
12 a$ = INKEY$: IF a$ = "" THEN 12
CLS
LINE (190, 195)-(255, 300), 9, BF
LINE (192, 197)-(253, 298), 0, B
END SUB

SUB youlose
18 b$ = INKEY$: IF b$ = "" THEN 18
CALL hzk24(250, 200, 9, "很遗憾你输了")
16 a$ = INKEY$: IF a$ = "" THEN 16
END SUB

SUB youwin
19 b$ = INKEY$: IF b$ = "" THEN 19
PRINT "cici1234"
CALL hzk24(250, 200, 9, "恭喜你赢了")
CALL hzk24(250, 225, 9, "高级密码在最上方")
17 a$ = INKEY$: IF a$ = "" THEN 17
END SUB

