package com.harmonygames.harmonyengine.utils;

import com.harmonygames.harmonyengine.Log;

import java.io.*;

public class FileUtils {

    public static String readFromFile(String location) {
        if(!location.startsWith("/")) location = "/" + location;

        InputStream inputStream = FileUtils.class.getResourceAsStream(location);
        if(inputStream == null) {
            Log.fatalError("Could not read from a file that doesn't exist!\n" +
                    "\tFile Location: '" + location + "'\n" +
                    "\tWhat was returned: null");
            return null;
        }

        InputStreamReader streamReader = new InputStreamReader(inputStream);
        BufferedReader bufferedReader = new BufferedReader(streamReader);

        StringBuilder builder = new StringBuilder();
        String line;

        try {
            while ((line = bufferedReader.readLine()) != null) {
                builder.append(line).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return builder.toString();
    }

}
