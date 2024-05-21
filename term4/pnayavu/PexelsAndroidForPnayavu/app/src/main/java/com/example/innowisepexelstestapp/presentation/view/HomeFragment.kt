package com.example.innowisepexelstestapp.presentation.view

import android.os.Bundle
import android.view.View
import androidx.core.widget.doAfterTextChanged
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.StaggeredGridLayoutManager
import by.kirich1409.viewbindingdelegate.viewBinding
import com.example.innowisepexelstestapp.R
import com.example.innowisepexelstestapp.databinding.FragmentHomeBinding
import com.example.innowisepexelstestapp.di.injectViewModel
import com.example.innowisepexelstestapp.model.Category
import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.presentation.rv.RvCategoryAdapter
import com.example.innowisepexelstestapp.presentation.rv.RvPhotoAdapter
import com.example.innowisepexelstestapp.presentation.viewmodel.HomeViewModel

class HomeFragment : Fragment(R.layout.fragment_home),
    RvPhotoAdapter.ClickListener,
    RvCategoryAdapter.ClickListener {

    private val mViewBinding by viewBinding(FragmentHomeBinding::bind)
    private val mViewModel: HomeViewModel by injectViewModel() //todo попробовать by viewmodels
    private val mRvPhotoAdapter: RvPhotoAdapter = RvPhotoAdapter(this,
        showAuthorName = false)
    private val mRvCategoryAdapter: RvCategoryAdapter = RvCategoryAdapter(this)

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        setViewsPresets()
        setupListeners()
        setupObservers()
    }

    override fun onClickPhoto(photoPexels: PhotoPexels) {
        mViewModel.onClickPhoto(photoPexels)
    }

    override fun onClickCategory(category: Category, position: Int) {
        mViewModel.onClickCategory(category, position)
    }

    private fun setViewsPresets() = with(mViewBinding) {
        homeRv.layoutManager = StaggeredGridLayoutManager(2,
            StaggeredGridLayoutManager.VERTICAL)
        categoryRv.layoutManager = LinearLayoutManager(context,
            LinearLayoutManager.HORIZONTAL, false)

        homeRv.adapter = mRvPhotoAdapter
        categoryRv.adapter = mRvCategoryAdapter
        categoryRv.setItemViewCacheSize(7)
    }

    private fun setupListeners() = with(mViewBinding) {
        var searchBarText = ""
        bnvFavorite.setOnClickListener {
            mViewModel.navigateToFavorite()
        }
        tvTryAgain.setOnClickListener {
            mViewModel.addPhotos()
            mViewModel.setCategories()
        }
        searchBarCloseIcon.setOnClickListener {
            mViewModel.onSearchBarCloseIcon()
        }
        searchBarEditText.doAfterTextChanged {
            searchBarText = searchBarEditText.text.toString().trim()
            mViewModel.doAfterTextChanged(it!!)
        }
        searchBarSearchIcon.setOnClickListener {
            mViewModel.addQueryPhotos(searchBarText)
        }
        homeRv.addOnScrollListener(object : RecyclerView.OnScrollListener() {
            override fun onScrolled(recyclerView: RecyclerView, dx: Int, dy: Int) {
                super.onScrolled(recyclerView, dx, dy)
                //mViewModel.onScrolledRv(recyclerView, searchBarText) //todo тут убрал, дабы проблем не было
            }
        })
    }

    private fun setupObservers() = with(mViewBinding) {
        mViewModel.ldOnCloseButton.observe(viewLifecycleOwner) {
            searchBarEditText.text.clear()
            searchBarEditText.clearFocus()
            mRvCategoryAdapter.categories.forEach { category ->
                category.isActive = false
            }
            mRvCategoryAdapter.notifyDataSetChanged()
        }
        mViewModel.ldSearchBarCloseIconVisibility.observe(viewLifecycleOwner) {
            searchBarCloseIcon.visibility = it
        }
        mViewModel.ldIvNoNetworkVisibility.observe(viewLifecycleOwner) {
            ivNonetwork.visibility = it
        }
        mViewModel.ldTvTryAgainVisibility.observe(viewLifecycleOwner) {
            tvTryAgain.visibility = it
        }
        mViewModel.ldAddPhotoList.observe(viewLifecycleOwner) {
            mRvPhotoAdapter.addPhotoList(it)
        }
        mViewModel.ldCreateNewPhotoList.observe(viewLifecycleOwner) {
            mRvPhotoAdapter.createNewPhotoList(it)
        }
        mViewModel.ldAddCategoryList.observe(viewLifecycleOwner) {
            mRvCategoryAdapter.addCategories(it)
        }
        mViewModel.ldProgressBarVisibility.observe(viewLifecycleOwner) {
            progressBar.visibility = it
        }
        mViewModel.ldShowAnim.observe(viewLifecycleOwner) {
            homeRv.startAnimation(it)
        }
        mViewModel.ldSetActiveCategory.observe(viewLifecycleOwner) {
            mRvCategoryAdapter.categories.forEach { category ->
                category.isActive = false
            }
            mRvCategoryAdapter.categories[it].isActive = true
            mRvCategoryAdapter.notifyDataSetChanged()
        }
        mViewModel.ldSetEditTextCategoryName.observe(viewLifecycleOwner) {
            searchBarEditText.text = it
        }
    }
}