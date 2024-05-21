package com.example.innowisepexelstestapp.repository.pexelsapi

import android.util.Log
import okhttp3.OkHttpClient
import okhttp3.Request
import okhttp3.Response

const val KEY = "1yRhwLBuxcoFBCLNlvFi7d00HeHhnv7fOzvYXsYTrbVBUV0RFk157lqx"

const val URL_GET_CURATED = "https://api.pexels.com/v1/curated"
const val URL_GET_FEATURED_COLLECTIONS = "https://api.pexels.com/v1/collections/featured"
const val URL_GET_SEARCH = "https://api.pexels.com/v1/search"

const val PER_PAGE_FEATURED_COLLECTIONS = "per_page=7"
const val PER_PAGE_30 = "per_page=30"
const val PAGE = "page="
const val QUERY = "query="

const val serverIp = "192.168.2.113"
const val serverPort = 8080

class PexelsNetworkClient(private val mClient: OkHttpClient) {

    private var pageCurated: Int = 1
    private var pageQuery: Int = 0
    private var pagePnayavu: Int = 0


    fun getResponseWithFeaturedCategories(): Response {
        val request = Request.Builder()
            .url("http://$serverIp:$serverPort/collection/all?page=${pageQuery++}&perPage=10")
            .get()
            .build()
        return mClient.newCall(request).execute()
    }

    fun getResponseWithQueryPhotos(query: String): Response {
        Log.e("customLog", "QUERY")
        val request = Request.Builder()
            .url("http://$serverIp:$serverPort/collection?query=$query")
            .get()
            .build()
        return mClient.newCall(request).execute()
    }


    fun getResponseWithCuratedPhotos(): Response {

        val url = "http://$serverIp:$serverPort/photo?page=${pagePnayavu++}&perPage=10"

        val request = Request.Builder()
            .url(url)
            .get()
            .build()
        return mClient.newCall(request).execute()
    }


}