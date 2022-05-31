def check_invalid_input(str_my):
    check=0
    if not str_my.isdigit() :
        check=1
            #可為-1
    if str_my[0]=='0' :
        check=1
    if str_my[0]=='-' :
        check=0
        num = int(str_my)
        num = -num
        num = str(num)
        if not num.isdigit() :
            check = 1
    return check
def AVG_printer(condition):
    invalid_condition = 0
    tempt_grade = 0 
    sum_of_grades = 0
    pointer=0
    while invalid_condition == 0:
        grade =input("please input your score:\n")
        invalid_condition = check_invalid_input(grade)
        if invalid_condition == 0:
            tempt_grade = int(grade)  #/改成數字確認大小
            grade = ''
            if tempt_grade<=100 and tempt_grade>=0:
                sum_of_grades += tempt_grade
                pointer +=1
            elif tempt_grade == -1:
                invalid_condition=2
            else:
                invalid_condition=1
    if invalid_condition==1 :
        condition = input("Invalid input! Do you want to input another set of grades? (Y/N): ")
        if condition=='Y' or condition[0]=='y':
            print("new set bigin:\n")
            return 1
        else:
            print("finish!\n")
            return 0
    elif invalid_condition==2:
        if pointer ==0:
            print('you didnt input any number yet,please try again!\n')
        else:
            print("the Average of these grades is: ",round((float)(sum_of_grades/pointer),2)) 
            print("\nnumber of times user inputs: ",pointer)
        condition = input("\nDo you want to input another set of grades? (Y/N):")
        if condition=='Y' or condition=='y':
            print("new set bigin:\n")
            return 1
        else:
            print("finish!\n")
            return 0

loop_condition = 'N'
conti_break=1 
print('Notice: # the AVG result will show up if you input -1 #\n')
while conti_break==1:
    #$conti_break==0的話代表不打算繼續執行了
    conti_break = AVG_printer(loop_condition)
    
