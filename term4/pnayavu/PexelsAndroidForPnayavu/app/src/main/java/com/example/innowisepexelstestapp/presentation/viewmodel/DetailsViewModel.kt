package com.example.innowisepexelstestapp.presentation.viewmodel

import android.widget.ImageView
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.example.innowisepexelstestapp.R
import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.usecase.DeleteImageFromRoomUseCase
import com.example.innowisepexelstestapp.usecase.DownloadImageUseCase
import com.example.innowisepexelstestapp.usecase.SaveImageIntoRoomUseCase
import com.example.innowisepexelstestapp.util.ResourceProvider
import com.github.terrakok.cicerone.Router
import javax.inject.Inject

class DetailsViewModel @Inject constructor(
    private val mRouter: Router,
    private val mResourceProvider: ResourceProvider,
    private val saveImageIntoRoomUseCase: SaveImageIntoRoomUseCase,
    private val deleteImageIntoRoomUseCase: DeleteImageFromRoomUseCase,
    private val downloadImageUseCase: DownloadImageUseCase
) : ViewModel() {

    private val _ldShowToast: MutableLiveData<String> = MutableLiveData()

    val ldShowToast: LiveData<String> = _ldShowToast


    fun onDownloadBtn(imageUrl: String) {
        downloadImageUseCase.execute(imageUrl)
        _ldShowToast.value = mResourceProvider.getStringRes(R.string.downloading)
    }

    fun onBackBtn() {
        mRouter.exit()
    }

    fun onFavoriteBtn(isItLikedPhoto: Boolean, view: ImageView, photoPexels: PhotoPexels) {
        // I tried to set the image through the LiveData and using the ResourceProvider,
        // but because the image is SVG, it is not set normally. So i set directly

        if (isItLikedPhoto) {
            view.setImageResource(R.drawable.ic_favorite_inactive)
            deleteImageIntoRoomUseCase.execute(photoPexels)
            _ldShowToast.value = mResourceProvider.getStringRes(R.string.deleted)
        } else {
            view.setImageResource(R.drawable.ic_favorite_active)
            saveImageIntoRoomUseCase.execute(photoPexels)
            _ldShowToast.value = mResourceProvider.getStringRes(R.string.saved)
        }

    }

    fun setFavoriteBtnImage(mIsItLikedPhotoArg: Boolean, favoriteBtn: ImageView) {
        // I tried to set the image through the LiveData and using the ResourceProvider,
        // but because the image is SVG, it is not set normally. So i set directly
        if(mIsItLikedPhotoArg) {
            favoriteBtn.setImageResource(R.drawable.ic_favorite_active)
        }
    }
}