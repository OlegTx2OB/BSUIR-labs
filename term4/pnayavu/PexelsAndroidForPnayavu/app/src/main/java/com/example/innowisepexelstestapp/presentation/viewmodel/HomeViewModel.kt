package com.example.innowisepexelstestapp.presentation.viewmodel

import android.annotation.SuppressLint
import android.text.Editable
import android.util.Log
import android.view.View
import android.view.animation.AlphaAnimation
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.StaggeredGridLayoutManager
import com.example.innowisepexelstestapp.model.Category
import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.presentation.navigation.Screens
import com.example.innowisepexelstestapp.repository.NetworkManager
import com.github.terrakok.cicerone.Router
import io.reactivex.Observable
import io.reactivex.Single
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.disposables.Disposable
import io.reactivex.schedulers.Schedulers
import java.util.concurrent.TimeUnit
import javax.inject.Inject

class HomeViewModel @Inject constructor(
    private val mRouter: Router,
    private val mNetworkManager: NetworkManager,
) : ViewModel() {

    private val _ldOnCloseButton: MutableLiveData<Unit> = MutableLiveData()
    private val _ldSearchBarCloseIconVisibility: MutableLiveData<Int> = MutableLiveData()
    private val _ldAddPhotoList: MutableLiveData<List<PhotoPexels>> = MutableLiveData()
    private val _ldCreateNewPhotoList: MutableLiveData<List<PhotoPexels>> = MutableLiveData()
    private val _ldAddCategoryList: MutableLiveData<List<Category>> = MutableLiveData()
    private val _ldIvNoNetworkVisibility: MutableLiveData<Int> = MutableLiveData()
    private val _ldTvTryAgainVisibility: MutableLiveData<Int> = MutableLiveData()
    private val _ldProgressBarVisibility: MutableLiveData<Int> = MutableLiveData()
    private val _ldShowAnim: MutableLiveData<AlphaAnimation> = MutableLiveData()
    private val _ldSetActiveCategory: MutableLiveData<Int> = MutableLiveData()
    private val _ldSetEditTextCategoryName: MutableLiveData<Editable> = MutableLiveData()

    val ldOnCloseButton: LiveData<Unit> = _ldOnCloseButton
    val ldSearchBarCloseIconVisibility: LiveData<Int> = _ldSearchBarCloseIconVisibility
    val ldAddPhotoList: LiveData<List<PhotoPexels>> = _ldAddPhotoList
    val ldCreateNewPhotoList: LiveData<List<PhotoPexels>> = _ldCreateNewPhotoList
    val ldAddCategoryList: LiveData<List<Category>> = _ldAddCategoryList
    val ldIvNoNetworkVisibility: LiveData<Int> = _ldIvNoNetworkVisibility
    val ldTvTryAgainVisibility: LiveData<Int> = _ldTvTryAgainVisibility
    val ldProgressBarVisibility: LiveData<Int> = _ldProgressBarVisibility
    val ldShowAnim: LiveData<AlphaAnimation> = _ldShowAnim
    val ldSetActiveCategory: LiveData<Int> = _ldSetActiveCategory
    val ldSetEditTextCategoryName: LiveData<Editable> = _ldSetEditTextCategoryName

    private val queryNamesList = mutableListOf("")

    private var disposable: Disposable? = null

    init {
        addPhotos()
        setCategories()
    }

    @SuppressLint("CheckResult")
    fun doAfterTextChanged(editable: Editable) {
        val text = editable.toString().trim()
        if (text.isNotEmpty()) {
            _ldSearchBarCloseIconVisibility.value = View.VISIBLE

            disposable?.dispose()
            disposable = Observable.timer(1000, TimeUnit.MILLISECONDS)
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe {
                    addQueryPhotos(text)
                }

        } else {
            _ldSearchBarCloseIconVisibility.value = View.GONE
            disposable?.dispose()
        }
    }

    fun addQueryPhotos(query: String) {
        queryNamesList.add(query)
        observePhotos(mNetworkManager.getQueryPhotos(query))
    }

    fun addPhotos() {
        queryNamesList.add("")
        observePhotos(mNetworkManager.getCuratedPhotos())
    }

    @SuppressLint("CheckResult")
    private fun observePhotos(singleList: Single<List<PhotoPexels>>) {
        singleList.observeOn(AndroidSchedulers.mainThread())
            .subscribe({ photos ->
                _ldIvNoNetworkVisibility.value = View.GONE
                _ldTvTryAgainVisibility.value = View.GONE
                chooseSetPhotoType(photos)

                _ldProgressBarVisibility.value = View.INVISIBLE
            }, {
                _ldIvNoNetworkVisibility.value = View.VISIBLE
                _ldTvTryAgainVisibility.value = View.VISIBLE
            })
        showRvAlphaAnimation()
    }

    fun onClickPhoto(photoPexels: PhotoPexels) {
        mRouter.navigateTo(Screens.detailsFragment(photoPexels, isItLikedPhoto = false))
    }

    fun onClickCategory(category: Category, position: Int) {
        _ldSetActiveCategory.value = position
        _ldSetEditTextCategoryName.value = Editable.Factory.getInstance()
            .newEditable(category.name)
    }

    fun onSearchBarCloseIcon() {
        _ldOnCloseButton.value = Unit
        addPhotos()
    }

    fun navigateToFavorite() {
        mRouter.navigateTo(Screens.favoriteFragment())
    }

    @SuppressLint("CheckResult")
    fun setCategories() {
        mNetworkManager.getCategories()
            .observeOn(AndroidSchedulers.mainThread())
            .subscribe({ categories ->
                _ldAddCategoryList.value = categories
            }, {

            })
    }

    private fun showRvAlphaAnimation() {
        val fadeInAnimation = AlphaAnimation(0f, 1f)
        fadeInAnimation.duration = 300

        _ldShowAnim.value = fadeInAnimation
    }

    private var isNewUploadAllowed = true
    @SuppressLint("CheckResult")
    fun onScrolledRv(recyclerView: RecyclerView, text: String) {
        //delay on 0.2 sec to avoid too frequent handling
        if (isNewUploadAllowed) {

            isNewUploadAllowed = false

            val layoutManager = recyclerView.layoutManager as StaggeredGridLayoutManager
            val lastVisibleItemPositions = layoutManager
                .findLastVisibleItemPositions(null)
            val totalItemCount = layoutManager.itemCount
            val maxVisibleItemPosition = lastVisibleItemPositions.maxOrNull()

            if (maxVisibleItemPosition == totalItemCount - 1) {
                Log.w("customLog", ">SUCCESSFULLY NEW RESPONSE")
                if (text.isEmpty()) {
                    addPhotos()
                } else {
                    addQueryPhotos(text)
                }
            }

            Observable.timer(200, TimeUnit.MILLISECONDS)
                .subscribeOn(Schedulers.io())
                .observeOn(Schedulers.io())
                .subscribe {
                    isNewUploadAllowed = true
                }

        }
    }

    /**
     * This method checks whether the last request matches the second to last one.
     * if it matches call livedata with adding photos.
     * if it does not match, then the old photos are deleting and new ones are adding
     */
    private fun chooseSetPhotoType(photos: List<PhotoPexels>) {
        if (queryNamesList.last() == queryNamesList[queryNamesList.size - 2]) {
            _ldAddPhotoList.value = photos
        } else {
            _ldCreateNewPhotoList.value = photos
        }

    }

}