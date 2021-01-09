package com.harmonygames.harmonyengine.utils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class FileUtils {

    public static String readFromFile(File file) {
        StringBuilder source = new StringBuilder();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));

            String line;

            while((line = reader.readLine()) != null) {
                source.append(line).append("\n");
            }

            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return source.toString();
    }

}
