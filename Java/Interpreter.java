import java.io.*;
import java.util.*;

class Computer{
    int[] program = new int[1001];
    int[] register = new int[10];
    int pc = 0;
    int numInstructions = 1;

    public Computer(){}

    public void addProgram(int pos, int value){
        program[pos] = value;
    }

    public int run(){
        while(this.pc < 1000){
            int instruction = program[pc];

            // Jump if register is 0
            if (instruction < 100){
                int dRegister = instruction / 10;
                int sRegister = instruction % 10;

                if (register[sRegister] != 0){
                    this.pc = register[dRegister];
                    this.pc--; // Subtract 1 so we can add one again
                }
            }

            // Halt
            else if (instruction < 200){
                break;
            }

            // Set register to value
            else if (instruction < 300){
                instruction -= 200;
                int dRegister = instruction / 10;
                int n = instruction % 10;
                register[dRegister] = n;
            }

            // Add value to register
            else if (instruction < 400){
                instruction -= 300;
                int dRegister = instruction / 10;
                int n = instruction % 10;
                register[dRegister] = (register[dRegister] + n) % 1000;
            }

            // Multiply value to register
            else if (instruction < 500){
                instruction -= 400;
                int dRegister = instruction / 10;
                int n = instruction % 10;
                register[dRegister] = (register[dRegister] * n) % 1000;
            }

            // Copy register
            else if (instruction < 600){
                instruction -= 500;
                int dRegister = instruction / 10;
                int sRegister = instruction % 10;
                register[dRegister] = register[sRegister];
            }

            // Add register to register
            else if (instruction < 700){
                instruction -= 600;
                int dRegister = instruction / 10;
                int sRegister = instruction % 10;
                register[dRegister] = (register[dRegister] + register[sRegister]) % 1000;
            }
            
            // Multiply register to register
            else if (instruction < 800){
                instruction -= 700;
                int dRegister = instruction / 10;
                int sRegister = instruction % 10;
                register[dRegister] = (register[dRegister] * register[sRegister]) % 1000;
            }

            // Set register to RAM value
            else if (instruction < 900){
                instruction -= 800;
                int dRegister = instruction / 10;
                int aRegister = instruction % 10;
                register[dRegister] = program[register[aRegister]];
            }

            // Update RAM
            else if (instruction < 1000){
                instruction -= 900;
                int sRegister = instruction / 10;
                int aRegister = instruction % 10;
                program[register[aRegister]] = register[sRegister];
            }

            // Update PC and number of Instructions
            this.pc++;
            this.numInstructions++;
        }

        return this.numInstructions;
    }
}

public class Interpreter{
    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        Computer computer = new Computer();
        int i = 0;

        String input;
        while ((input = r.readLine()) != null){
            computer.addProgram(i, Integer.parseInt(input));
            i++;
        }

        System.out.println(computer.run());
    }
    

    public static void main(String[] args) throws IOException{
        Interpreter interpreter = new Interpreter();
        interpreter.run();
    }
}

