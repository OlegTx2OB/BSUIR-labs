package com.example.innowisepexelstestapp.repository.downloadmanager

import android.app.DownloadManager
import android.content.Context
import android.net.Uri
import android.os.Environment
import android.webkit.CookieManager
import android.webkit.URLUtil
import androidx.core.content.ContextCompat.getSystemService
import com.example.innowisepexelstestapp.repository.DownloadFilesManager

class DownloadFilesManagerImpl(private val mAppContext: Context) : DownloadFilesManager {

    override fun download(url: String) {
        val request = DownloadManager.Request(Uri.parse(url))
        val title = URLUtil.guessFileName(url, null, null)
        request.setTitle(title)
        request.setDescription("Downloading file, please wait...")
        val cookie = CookieManager.getInstance().getCookie(url)
        request.addRequestHeader("cookie", cookie)
        request.setNotificationVisibility(DownloadManager
            .Request
            .VISIBILITY_VISIBLE_NOTIFY_COMPLETED)
        request.setDestinationInExternalPublicDir(Environment.DIRECTORY_DOWNLOADS, title)

        val downloadManager = getSystemService(mAppContext, DownloadManager::class.java)
        downloadManager!!.enqueue(request)
    }
}