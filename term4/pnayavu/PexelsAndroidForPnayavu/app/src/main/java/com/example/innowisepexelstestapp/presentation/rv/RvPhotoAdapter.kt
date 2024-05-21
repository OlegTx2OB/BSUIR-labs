package com.example.innowisepexelstestapp.presentation.rv

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.example.innowisepexelstestapp.R
import com.example.innowisepexelstestapp.databinding.RvPhotoItemBinding
import com.example.innowisepexelstestapp.model.PhotoPexels
import com.squareup.picasso.Picasso
import io.reactivex.Observable
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.schedulers.Schedulers

class RvPhotoAdapter(private val mListener: ClickListener, private val showAuthorName: Boolean) :
    RecyclerView.Adapter<RvPhotoAdapter.PhotoHolder>() {

    private val photoPexelsArray = mutableListOf<PhotoPexels>()

    class PhotoHolder(view: View, isItForFavoriteScreen: Boolean) : RecyclerView.ViewHolder(view) {
        private val binding = RvPhotoItemBinding.bind(view)

        init {
            if (isItForFavoriteScreen) {
                binding.authorName.visibility = View.VISIBLE
            }
        }

        fun bind(photoPexels: PhotoPexels, listener: ClickListener) = with(binding) {
            Picasso.get()
                .load(photoPexels.sources.medium)
                .placeholder(R.drawable.ic_imagestub)
                .into(rvHomeItem)

            authorName.text = photoPexels.photographer

            itemView.setOnClickListener {
                listener.onClickPhoto(photoPexels)
            }
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PhotoHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.rv_photo_item, parent, false)
        return PhotoHolder(view, showAuthorName)
    }

    override fun onBindViewHolder(holder: PhotoHolder, position: Int) {
        holder.bind(photoPexelsArray[position], mListener)
    }

    override fun getItemCount(): Int {
        return photoPexelsArray.size
    }

    @SuppressLint("CheckResult")
    fun addPhotoList(photoPexelsList: List<PhotoPexels>) {
        val newPhotoList = mutableListOf<PhotoPexels>()
        Observable.just(photoPexelsList)
            .subscribeOn(Schedulers.computation())
            .observeOn(AndroidSchedulers.mainThread())
            .subscribe {
                photoPexelsArray.clear()
                photoPexelsArray.addAll(photoPexelsList)
                notifyDataSetChanged()
            }
    }

    @SuppressLint("CheckResult")
    fun createNewPhotoList(photoPexelsList: List<PhotoPexels>) {
        Observable.just(photoPexelsList)
            .subscribeOn(Schedulers.computation())
            .observeOn(AndroidSchedulers.mainThread())
            .subscribe {
                photoPexelsArray.clear()
                photoPexelsArray.addAll(photoPexelsList)
                notifyDataSetChanged()
            }
    }


    interface ClickListener {
        fun onClickPhoto(photoPexels: PhotoPexels)
    }
}