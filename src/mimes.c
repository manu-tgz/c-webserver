char* mime;
char* exts[] = {".json",
                ".ogg",
                ".pdf",
                ".sql",
                ".xml",
                ".zip",
                ".mpeg",
                ".ogg",
                ".wave",
                ".webm",
                ".gif",
                ".jpeg",
                ".png",
                ".css",
                ".csv",
                ".html",
                ".xml", 
                ".mp4",
                ".ogg",
                ".webm"

};
char* mimes[] = {
                "application/json",
                "application/ogg",
                "application/pdf",
                "application/sql",
                "application/xml",
                "application/zip",

                "audio/mpeg",
                "audio/ogg",
                "audio/wave",
                "audio/webm",

                "image/gif",
                "image/jpeg",
                "image/png", 

                "text/css",
                "text/csv",
                "text/html",
                "text/xml", 

                "video/mp4",
                "video/ogg",
                "video/webm"
};

int check_mime(char* ext)
{
    for (int i = 0; i < 20; i++)
        if(strcmp(ext,exts[i])==0)
        {
            mime = mimes[i];
            return 1;
        }
    return -1;    
}