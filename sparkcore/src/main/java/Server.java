import javax.servlet.MultipartConfigElement;
import javax.servlet.http.*;
import spark.Request;

import spark.Response;
import spark.Route;
import spark.Spark;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Collection;
import java.util.Set;

import static spark.Spark.*;

/**
 * Created by Vadim on 05/05/17.
 */
public class Server {

    private static void enableCORS(final String origin, final String methods, final String headers) {

        options("/*", (request, response) -> {

            String accessControlRequestHeaders = request.headers("Access-Control-Request-Headers");
            if (accessControlRequestHeaders != null) {
                response.header("Access-Control-Allow-Headers", accessControlRequestHeaders);
            }

            String accessControlRequestMethod = request.headers("Access-Control-Request-Method");
            if (accessControlRequestMethod != null) {
                response.header("Access-Control-Allow-Methods", accessControlRequestMethod);
            }
            return "OK";
        });

        before((request, response) -> {
            response.header("Access-Control-Allow-Origin", origin);
            response.header("Access-Control-Request-Method", methods);
            response.header("Access-Control-Allow-Headers", headers);
            // Note: this may or may not be necessary in your particular application
            response.type("application/json");
        });
    }

    public static void main(String[] args) {
        setPort(8080);
        if (args.length != 1) {
            System.err.println("Invalid arguments!");
            return;
        }

        enableCORS("*", "POST GET OPTIONS", "Content-Type");

        final String checkerLocation = args[0];

        post("/submit", (request, response) -> {

            MultipartConfigElement multipartConfigElement = new MultipartConfigElement("/tmp");
            request.raw().setAttribute("org.eclipse.multipartConfig", multipartConfigElement);

            InputStream is = null;
            OutputStream os = null;


            try {
                Part part = request.raw().getPart("uploaded_file");
                is = part.getInputStream();
                File solutionFile = null;
                String targetFile = null;
                final String language = request.queryParams("language");
                System.out.println(language);
                if (language.equals("C++")) {
                    targetFile = "testing.cpp";
                } else {
                    targetFile = "Testing.java";
                }
                solutionFile = new File(checkerLocation + "/"
                        + request.queryParams("problem") + "/" + targetFile);
                System.out.println(solutionFile);
                os = new FileOutputStream(solutionFile);
                int read;
                byte[] bytes = new byte[1024];
                while ((read = is.read(bytes)) != -1) {
                    os.write(bytes, 0, read);
                }

            } catch (Exception e) {
                System.out.println(e.getLocalizedMessage());
                System.out.println("Error");
            } finally {
                if (is != null) {
                    try {
                        is.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                if (os != null) {
                    try {
                        os.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }


            Set<String> allParams = request.queryParams();

            if (!allParams.contains("problem")) {
                return "There is no queryParam: problem\n";
            }
            if (!allParams.contains("language")) {
                return "There is no queryParam: language\n";
            }

            final String language = request.queryParams("language");

            final String problem = request.queryParams("problem");
            String result = null;

            try {

                Process p = Runtime.getRuntime().exec(checkerLocation +
                        "/" + problem + "/main " + language);

                int x = p.waitFor();
                switch(x) {
                    case 0:
                        result = "OK";
                        break;
                    case 1:
                        result = "WA";
                        break;
                    case 2:
                        result = "TL";
                        break;
                    case 3:
                        result = "CE";
                        break;
                    case 4:
                        result = "PE";
                        break;
                    default:
                        result = "Unexpected behavior";
                }

            } catch (IOException | InterruptedException e) {
                return e.getMessage();
            }

            return result;
        });
    }

}
