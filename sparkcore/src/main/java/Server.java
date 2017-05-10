import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Set;

import static spark.Spark.*;

/**
 * Created by Vadim on 05/05/17.
 */
public class Server {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Invalid arguments!");
            return;
        }

        final String checkerLocation = args[0];

        get("/submit", (request, response) -> {
            System.out.println("GET");
            Set<String> allParams = request.queryParams();
            if (!allParams.contains("problem")) {
                return "There is no queryParam: problem\n";
            }
            if (!allParams.contains("language")) {
                return "There is no queryParam: language\n";
            }
            if (!allParams.contains("source")) {
                return "There is no queryParam: source\n";
            }

            File file;
                try {
                    file = new File(checkerLocation, request.queryParams("problem") + "/solution.cpp");
                    if (!file.exists()) {
                        boolean mkdirs = file.getParentFile().mkdirs();
                        if (!mkdirs) {
                            return "Mkdirs false";
                        }
                        boolean created = file.createNewFile();
                        if (!created) {
                            return "File was not created!";
                        }
                    }
                } catch (Exception e) {
                    return e.getMessage();
                }

                try {
                    Files.write(file.toPath(), request.queryParams("source").getBytes());
                } catch (IOException e) {
                    return e.getMessage();
                }

                try {
                    Process executing = Runtime.getRuntime().exec(checkerLocation + "/runner");
                } catch (IOException e) {
                    return e.getMessage();
                }

                return "Checking...";
        });
    }

}
