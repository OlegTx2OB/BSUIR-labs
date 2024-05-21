package com.example.innowisepexelstestapp.repository.room

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import com.example.innowisepexelstestapp.dto.PhotoPexelsDto

@Dao
interface PhotoPexelsDao {
    @Query("SELECT * FROM PhotoPexelsDto")
    fun getAllPhotoPexels(): List<PhotoPexelsDto> //todo хз может ли автоматически создаться оболочка Single

    @Insert(onConflict = OnConflictStrategy.IGNORE)
    fun insertPhotoPexels(photoPexelsDto: PhotoPexelsDto)

    @Delete
    fun deletePhotoPexels(photoPexelsDto: PhotoPexelsDto)
}