package com.example.innowisepexelstestapp.usecase

import com.example.innowisepexelstestapp.repository.DownloadFilesManager

class DownloadImageUseCase(private val downloadFilesManager: DownloadFilesManager) {
    fun execute(url: String) {
        downloadFilesManager.download(url)
    }
}