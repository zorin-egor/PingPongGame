package ru.simpleapps.pingpong;


import android.app.Application;
import org.acra.ACRA;
import org.acra.ReportingInteractionMode;
import org.acra.annotation.ReportsCrashes;

import static org.acra.ReportField.ANDROID_VERSION;
import static org.acra.ReportField.APP_VERSION_CODE;
import static org.acra.ReportField.PHONE_MODEL;
import static org.acra.ReportField.STACK_TRACE;

@ReportsCrashes(customReportContent = { APP_VERSION_CODE, ANDROID_VERSION, PHONE_MODEL, STACK_TRACE },
        mailTo = "testsimpleapps@gmail.com",
        mode = ReportingInteractionMode.DIALOG,
        resToastText = R.string.acra_crush_title,
        resDialogText = R.string.acra_crush_message_text,
        resDialogIcon = android.R.drawable.ic_dialog_info,
        resDialogTitle = R.string.acra_crush_title,
        resDialogCommentPrompt = R.string.acra_crush_message_comment,
        resDialogOkToast = R.string.acra_crush_ok)

public class GameApplication extends Application {

    public void onCreate() {
        super.onCreate();
        ACRA.init(this);
    }
}