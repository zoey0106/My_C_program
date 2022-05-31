import java.util.Scanner;

public class AVG {
    
    
    public static int invalid_input(String str) {
        
        char[] char_str = str.toCharArray();
        
        int check = 0;
        for(int i=0;i< str.replace(" ", "").length() ;i++){
            if(i==0){
                if(char_str[i]<48||char_str[i]>58){
                    check=1;
                }
                if(char_str[i]=='-'){
                    check=0;
                }
                if(char_str[i]=='0'){
                    check=1;
                }
            }
            else{//0~9
                if(char_str[i]<47||char_str[i]>58){
                    check=1;
                }
            }
            if(check==1){
                break;
            }
        }
        return check;
    }
    
    public static int AVG_printer(String condition){
        int invalid_condition = 0;
        Scanner scanner = new Scanner(System.in);
        String grade;
        int tempt_grade = 0; 
        int sum_of_grades = 0;
        int pointer = 0;
        char[] condition_cahr;
        while(invalid_condition==0){
            System.out.println("please input your score:");
            grade = scanner.next();
            invalid_condition = invalid_input(grade);
            if(invalid_condition == 0){
                tempt_grade=Integer.parseInt(grade);
                grade="";
                if(tempt_grade<=100&&tempt_grade>=0){
                    sum_of_grades += tempt_grade;
                    pointer++;
                }
                else if(tempt_grade == -1){
                    invalid_condition=2;
                }
                else{
                    invalid_condition=1;
                }
            }
        }
        if(invalid_condition==1){
            System.out.println("Invalid input! Do you want to input another set of grades? (Y/N): "); ;
            condition = scanner.next();
            condition_cahr = condition.toCharArray();

            if(condition_cahr[0]=='Y'||condition_cahr[0]=='y'){
                System.out.println("new set bigin:");
                return 1;
            }
            else{
                System.out.println("finish!");
                scanner.close();
                return 0;
            }
        }
        else if(invalid_condition==2){
            if(pointer>0){
                System.out.println("the Average of these grades is: " + (float)sum_of_grades/pointer); 
            }
            else{
                System.out.println("you didn't put in any number,please try again!");
            }
            
            System.out.println("number of times user inputs: " + pointer);
            System.out.println("Do you want to input another set of grades? (Y/N):");
            condition = scanner.next();
            condition_cahr = condition.toCharArray();
            if(condition_cahr[0]=='Y'||condition_cahr[0]=='y'){
                System.out.println("new set bigin:");
                return 1;
            }
            else{
                System.out.println("finish!");
                scanner.close();
                return 0;
            }
        }
        return -1;
    }
    
    public static void main(String[] args) {
        String loop_condition ="N";
        int  conti_break = 1;
        while(conti_break==1){
            conti_break = AVG_printer(loop_condition);
        }
    } // end main  
    
    
    
}
