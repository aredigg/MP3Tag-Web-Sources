# Apple Music Classical parser v1.00 for MP3Tag
# © 2025 All Rights Reserved
[Name]=Apple Music Classical
[BasedOn]=https://classical.music.apple.com/
[WordSeparator]=%20
[Encoding]=url-utf-8
[IndexFormat]=%_url%|%_preview%|%_coverurl%|%Title%|%Artist%|%Year%|%Kind%|%Work%
[MinAppVersionMac]=1.8.4
[MinAppVersionWin]=3.22
[Settings]=&Apple Music Classical#Settings….settings

[ParserScriptIndex]=...

FindLine "<script type=\"application/json\" id=\"serialized-server-data\">"
RegexpReplace ".*<script type=\"application/json\" id=\"serialized-server-data\">\[(.*)\]<\/script>.*" "$1"

json "on" "current"

# debug "on" "debug-index.txt"

json_select_object "intent"
	json_select "term"
	If "https://classical.music.apple.com/"
		OutputTo "FallbackItem"
		SayRest
		OutputTo "FallbackTerm"
		Say "Apple Music URL"
		Set "FoundWebURL" "True"
	Else
		OutputTo "FallbackItem"
		Say "https://classical.music.apple.com/"
		json_select "storefront"
		SayRest
		Say "/album/"
		json_select "term"
		SayNextNumber
		json_select "language"
		IfNot ""
			Say "?l="
			SayRest
		EndIf
		OutputTo "FallbackTerm"
		json_select "term"
		Say "Apple Music Classical ID: "
		SayNextNumber
	EndIf
	OutputTo "Output"
json_unselect_object

IfNotOutput "FoundWebURL"
	json_select_object "data"
		json_foreach "sections"
			json_select "id"
			If "search-results-empty-header"
				Set "Output"
				SayOutput "FallbackItem"
				Say "|"
				SayOutput "FallbackItem"
				Say "||"
				SayOutput "FallbackTerm"
				Say "||||"
			Else
				json_select "itemKind"
				IfNot "topSearchLockup"
					json_foreach "items"
						json_select "type"

						# Primary
						IfVar "listAlbums" "true"
							If "album"
								Set "FoundAlbum" "True"

								# %_url%
								Say "https://classical.music.apple.com"
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								Say "https://classical.music.apple.com"
								json_select "url"
								SayRest
								Say "|"

							EndIf
						EndIf
						IfVar "listSongs" "true"
							If "track"
								Set "FoundSong" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
						EndIf
						IfVar "listMusicVideos" "true"
							If "musicVideo"
								Set "FoundMusicVideo" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
						EndIf
						IfVar "listExtraVideos" "true"
							If "artistUploadedVideo"
								Set "FoundExtraVideo" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
						EndIf
						IfVar "listPlaylists" "true"
							If "playlist"
								Set "FoundPlaylist" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
						EndIf
						IfVar "listRadioStations" "true"
							If "radioStation"
								Set "FoundRadioStation" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
							If "appleCurator"
								Set "FoundRadioStation" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
						EndIf

						# Secondary
						IfOutput "FoundAlbum"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select "template"
									RegexpReplace "(.*)\/.*" "$1"
									SayRest
									Say "/120x120-50.jpg"
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select "title"
							SayRest
							Say "|"

							# %Artist%
							json_select "subtitle"
							SayRest
							Say "|"

							# %Year%
							json_select_object "action"
							IfNot ""
									json_select_object "header"
									IfNot ""
									    json_select "year"
            							SayNextNumber
    				                    json_unselect_object
                                    EndIf
								json_unselect_object
							EndIf
							Say "|"

							# %Kind%
							Say "Album"
							Say "|"

							# %Work%

							SayNewline
							Set "FoundAlbum"

						EndIf
						IfOutput "FoundSong"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select "template"
									RegexpReplace "(.*)\/.*" "$1"
									SayRest
									Say "/120x120-50.jpg"
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select_object "header"
							IfNot ""
         							json_select "title"
         							SayRest
                                json_unselect_object
							EndIf
							Say "|"

							# %Artist%
							json_select "subtitle"
							SayRest
							Say "|"

							# %Year%
							Say "|"

							# %Kind%
							Say "Track (Album)"
							Say "|"

							# %Work%
							json_select "title"
							SayRest

							SayNewline
							Set "FoundSong"

						EndIf
						IfOutput "FoundMusicVideo"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select_object "dictionary"
										json_select "url"
										RegexpReplace "(.*)\/.*" "$1"
										SayRest
										Say "/120x120-50.jpg"
									json_unselect_object
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select_many "titleLinks" "title" " / "
							SayRest
							Say "|"

							# %Artist%
							json_select_many "subtitleLinks" "title" ", "
							SayRest
							Say "|"

							# %Tracks%
							json_select "trackCount"
							Say "|"

							# %Kind%
							Say "Music Video"
							Say "|"

							# %Explicit%
							json_select "showExplicitBadge"
							If "1"
								Say "Yes"
							EndIf

							SayNewline
							Set "FoundMusicVideo"

						EndIf
						IfOutput "FoundExtraVideo"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select_object "dictionary"
										json_select "url"
										RegexpReplace "(.*)\/.*" "$1"
										SayRest
										Say "/120x120-50.jpg"
									json_unselect_object
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select_many "titleLinks" "title" " / "
							SayRest
							Say "|"

							# %Artist%
							json_select_many "subtitleLinks" "title" ", "
							SayRest
							Say "|"

							# %Tracks%
							json_select "trackCount"
							Say "|"

							# %Kind%
							Say "Video"
							Say "|"

							# %Explicit%
							json_select "showExplicitBadge"
							If "1"
								Say "Yes"
							EndIf

							SayNewline
							Set "FoundExtraVideo"

						EndIf
						IfOutput "FoundPlaylist"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select_object "dictionary"
										json_select "url"
										RegexpReplace "(.*)\/.*" "$1"
										SayRest
										Say "/120x120-50.jpg"
									json_unselect_object
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select_many "titleLinks" "title" " / "
							SayRest
							Say "|"

							# %Artist%
							json_select_many "subtitleLinks" "title" ", "
							SayRest
							Say "|"

							# %Tracks%
							json_select "trackCount"
							Say "|"

							# %Kind%
							Say "Playlist"
							Say "|"

							# %Explicit%
							json_select "showExplicitBadge"
							If "1"
								Say "Yes"
							EndIf

							SayNewline
							Set "FoundPlaylist"

						EndIf
						IfOutput "FoundRadioStation"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select_object "dictionary"
										json_select "url"
										RegexpReplace "(.*)\/.*" "$1"
										SayRest
										Say "/120x120-50.jpg"
									json_unselect_object
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select_many "titleLinks" "title" " / "
							SayRest
							Say "|"

							# %Artist%
							json_select_many "subtitleLinks" "title" ", "
							SayRest
							Say "|"

							# %Tracks%
							json_select "trackCount"
							Say "|"

							# %Kind%
							Say "Radio Station"
							Say "|"

							# %Explicit%
							json_select "showExplicitBadge"
							If "1"
								Say "Yes"
							EndIf

							SayNewline
							Set "FoundRadioStation"

						EndIf
					json_foreach_end
				EndIf
			EndIf
		json_foreach_end
	json_unselect_object
Else
	Set "Output"
	SayOutput "FallbackItem"
	Say "|"
	SayOutput "FallbackItem"
	Say "||"
	SayOutput "FallbackTerm"
	Say "||||"
	Set "FoundWebURL"
EndIf

json "off"

[ParserScriptAlbum]=...

IfNotOutput "Delimiter"
	OutputTo "Delimiter"
	IfVar "delimiter" "\\\\"
		Say "\\\\"
	EndIf
	IfVar "delimiter" ", "
		Say ", "
	EndIf
	IfVar "delimiter" ";"
		Say ";"
	EndIf
	IfVar "delimiter" "/"
		Say "/"
	EndIf
	IfVar "delimiter" "|"
		Say "$verticalBar()"
	EndIf
	IfVar "delimiter" " "
		Say " "
	EndIf
EndIf

FindLine "<script id=schema:music-album type="application/ld+json\">" 1 1
MoveLine 1 1

json "on" "current"

json_foreach "track"
	OutputTo "TRACKS"
	json_select "name"
	SayRest
	Say "|"

    OutputTo "TRACK"
    json_foreach_counter
    SayRest
	Say "|"

	OutputTo "TITLE"
	json_select "name"
	IfNotVar "originalTitles" "true"
		RegexpReplace "\(.*\)" ""
		RegexpReplace "\[.*\]" ""
		If ""
			Set "Skip_Comment" "True"
			json_select "name"
			SayRegexp "(?<=\()[^)]*(?=\))"
		Else
			SayRest
		EndIf
	Else
		SayRest
	EndIf
	Say "|"

	IfNotVar "originalTitles" "true"
		OutputTo "COMMENT"
		IfNotOutput "Skip_Comment"
			json_select "name"
			SayRegexp "(?<=\()[^)]*(?=\))"
			IfOutput "COMMENT"
				SayNewline
			EndIf
			SayRegexp "(?<=\[)[^)]*(?=\])"
			Set "Skip_Comment"
		EndIf
		Say "|"
	EndIf

	IfVar "addSortTitles" "true"
		OutputTo "TITLESORT"
		json_select "name"
		SayRest
		Say "|"
	EndIf

json_foreach_end

json "off"

FindLine "<script type=\"application/json\" id=\"serialized-server-data\">" 1 1
RegexpReplace ".*<script type=\"application/json\" id=\"serialized-server-data\">\[(.*)\]<\/script>.*" "$1"

json "on" "current"

# debug "on" "debug-album.txt"

json_select_object "data"
	IfNot ""
	json_select_object "header"
	IfNot ""
			OutputTo "COVERURL"
			json_select_object "artwork"
			IfNot ""
					json_select "template"
					IfVar "coverartSize" "Original quality"
						Replace "://is" "://a"
						Replace "-ssl.mzstatic.com/image/thumb/" ".mzstatic.com/us/r1000/0/"
					EndIf
					RegexpReplace "(.*)\/.*" "$1"
					SayRest
					# Width x Height - JPEG Quality
					IfVar "coverartSize" "600 pixels - 50 %"
						Say "/600x600-50.jpg"
					EndIf
					IfVar "coverartSize" "600 pixels - 90 %"
						Say "/600x600-90.jpg"
					EndIf
					IfVar "coverartSize" "1200 pixels - 50 %"
						Say "/1200x1200-50.jpg"
					EndIf
					IfVar "coverartSize" "1200 pixels - 90 %"
						Say "/1200x1200-90.jpg"
					EndIf
					IfVar "coverartSize" "2400 pixels - 50 %"
						Say "/2400x2400-50.jpg"
					EndIf
					IfVar "coverartSize" "2400 pixels - 90 %"
						Say "/2400x2400-90.jpg"
					EndIf
					IfVar "coverartSize" "3600 pixels - 50 %"
						Say "/3600x3600-50.jpg"
					EndIf
					IfVar "coverartSize" "3600 pixels - 90 %"
						Say "/3600x3600-90.jpg"
					EndIf
				json_unselect_object
			EndIf

			IfNotVar "skipiTunesTags" "true"
				IfNotOutput "ITUNESALBUMID"
					OutputTo "ITUNESALBUMID"
					json_select "id"
					SayNextNumber
				EndIf
			EndIf

			json_foreach "subtitleLinks"
				IfNot "0"

					OutputTo "ALBUMARTIST"
					IfOutput "ALBUMARTIST"
						SayOutput "Delimiter"
					EndIf
					json_select "title"

					Replace "Various Artists" ""
					Replace "Varios Artistas" ""
					Replace "Vários Artistas" ""
					Replace "Vários intérpretes" ""
					Replace "群星" ""
					Replace "群星" ""
					Replace "Eri Esittäjiä" ""
					Replace "Multi-interprètes" ""
					Replace "Verschiedene Interpreten" ""
					Replace "Verschillende artiesten" ""
					Replace "Artisti Vari" ""
					Replace "ヴァリアス・アーティスト" ""
					Replace "Diverse Artister" ""
					Replace "Разные артисты" ""
					Replace "Разные исполнители" ""
					Replace "Διάφοροι καλλιτέχνες" ""
					Replace "Blandade Artister" ""
					Replace "אמנים שונים" ""
					Replace "Çeşitli Sanatçılar" ""
					Replace "مختلف الفنانين" ""
					Replace "فنانون متنوعون" ""
					Replace "فنانون متعددون" ""
					Replace "Різні виконавці" ""
					Replace "รวมศิลปิน" ""
					Replace "Nhiều Nghệ Sĩ" ""
					IfNot ""
						json_select "title"
						SayRest
					EndIf

					IfVar "addSortTitles" "true"
						Set "ALBUMARTISTSORT"
						OutputTo "ALBUMARTISTSORT"
						SayOutput "ALBUMARTIST"
					EndIf

				EndIf
			json_foreach_end

			OutputTo "ALBUM"
			json_select "title"
			IfNotVar "originalTitles" "true"
				Replace " - Single" ""
				Replace " - EP" ""
				RegexpReplace "\(.*\)" ""
				RegexpReplace "\[.*\]" ""
			EndIf
			If ""
				json_select "title"
			EndIf
			SayRest

      		IfNotVar "originalTitles" "true"
				OutputTo "CONTENTGROUP"
				json_select "title"
				SayRegexp "(?<=\()[^)]*(?=\))"
				IfOutput "CONTENTGROUP"
				SayNewline
				EndIf
				SayRegexp "(?<=\[)[^)]*(?=\])"
            EndIf

 			IfVar "addSortTitles" "true"
				OutputTo "ALBUMSORT"
				json_select "title"
				SayRest
 			EndIf

			OutputTo "TOTALTRACKS"
			json_select "trackCount"
			SayNextNumber

			OutputTo "DURATION"
			json_select "totalDurationMs"
			SayNextNumber

			OutputTo "YEAR"
    		json_select "year"
    		IfNot ""
    		    SayRest
    		EndIf

			json_select_object "modalPresentationDescriptor"
			IfNot ""
				OutputTo "DESCRIPTION"
				json_select "paragraphText"
				SayRest
				IfVar "naturalTitles" "true"
					IfNotOutput "ALBUMARTIST"
						OutputTo "ALBUMARTIST"
						json_select "headerSubtitle"
						Replace "Various Artists" ""
						Replace "Varios Artistas" ""
						Replace "Vários Artistas" ""
						Replace "Vários intérpretes" ""
						Replace "群星" ""
						Replace "群星" ""
						Replace "Eri Esittäjiä" ""
						Replace "Multi-interprètes" ""
						Replace "Verschiedene Interpreten" ""
						Replace "Verschillende artiesten" ""
						Replace "Artisti Vari" ""
						Replace "ヴァリアス・アーティスト" ""
						Replace "Diverse Artister" ""
						Replace "Разные артисты" ""
						Replace "Разные исполнители" ""
						Replace "Διάφοροι καλλιτέχνες" ""
						Replace "Blandade Artister" ""
						Replace "אמנים שונים" ""
						Replace "Çeşitli Sanatçılar" ""
						Replace "مختلف الفنانين" ""
						Replace "فنانون متنوعون" ""
						Replace "فنانون متعددون" ""
						Replace "Різні виконавці" ""
						Replace "รวมศิลปิน" ""
						Replace "Nhiều Nghệ Sĩ" ""
						RegexpReplace "\s·\s\d*" ""
						IfNot ""
							json_select "headerSubtitle"
							RegexpReplace "\s·\s.*$" ""
							SayRest
						EndIf
					EndIf
					IfVar "addSortTitles" "true"
						Set "ALBUMARTISTSORT"
						OutputTo "ALBUMARTISTSORT"
						SayOutput "ALBUMARTIST"
					EndIf
				EndIf
				json_unselect_object
			EndIf

	   json_unselect_object
	EndIf

	json_foreach "sections"

		json_select "itemKind"
		If "containerDetailHeaderLockup"
			Set "ValidSection" "True"
		EndIf
		If "trackLockup"
			Set "ValidSection" "True"
		EndIf
		If "trackListFooter"
			Set "ValidSection" "True"
		EndIf
		If "ellipseLockup"
			Set "ValidSection" "True"
		EndIf
		If "credit"
			Set "ValidSection" "True"
		EndIf

		IfOutput "ValidSection"
			json_select_object "header"
        	IfNot ""
        			json_select_object "item"
                	IfNot ""
            				OutputTo "TEMP_WORK_DURATION"
            				json_select "duration"
            				SayRest
                        json_unselect_object
                    EndIf
                json_unselect_object
           	EndIf

		    Set "TEMP_LOCAL_ITEMCOUNT"
			json_foreach "items"
    			OutputTo "TEMP_LOCAL_ITEMCOUNT"
    			SayRest
				# Primary
				json_select "type"

				If "album"
					Set "SectionAlbum" "True"
				EndIf

				If "song"
					Set "SectionSong" "True"

					IfNotVar "skipiTunesTags" "true"
						OutputTo "ITUNESMEDIATYPE"
						Say "Normal"
						Say "|"
					EndIf

					IfNotVar "skipiTunesTags" "true"
   					    OutputTo "TEMP_IT"
						json_select "id"
						Replace "track-lockup - " ""
						SayUntil "-"
						SayUntil "-"
  						OutputTo "ITUNESCATALOGID"
						SayNextNumber
						Say "|"
						Set "TEMP_IT"
					EndIf

				EndIf

				If "musicVideo"
					Set "SectionSong" "True"

					IfNotVar "skipiTunesTags" "true"
						OutputTo "ITUNESMEDIATYPE"
						Say "Music Video"
						Say "|"
					EndIf

					IfNotVar "skipiTunesTags" "true"
						OutputTo "ITUNESCATALOGID"
							json_select "id"
							FindInLine "-" 2 1
							SayNextNumber
						Say "|"
					EndIf

				EndIf

				If "artist"
					Set "SectionArtist" "True"
				EndIf

				If "info"
					Set "SectionArtist" "True"
				EndIf

				IfOutput "SectionArtist"
				    OutputTo "INVOLVEDPEOPLE"
					json_select "subtitle"
					SayRest
					Say ":"
					json_select "title"
					SayRest
					Say ";"
				EndIf

				json_select "screenType"

				If "album"
					Set "SectionAlbum" "True"
				EndIf


				# Secondary
				json_foreach "subtitleLinks"
					IfNot "0"

						IfOutput "SectionAlbum"

						EndIf

						IfOutput "SectionSong"

							IfNotVar "naturalTitles" "true"

								OutputTo "ARTIST"
								IfOutput "TEMP_ARTIST"
									SayOutput "Delimiter"
								EndIf
								json_select "title"
								SayRest
								Set "TEMP_ARTIST" "True"

							EndIf

						EndIf

						json_select_object "segue"
						IfNot ""
							json_select_object "destination"
								json_select_object "contentDescriptor"
									json_select "kind"

									If "artist"
										json_select_object "identifiers"

											IfOutput "SectionAlbum"
												OutputTo "TEMP_ALBUMARTISTID"
												IfOutput "TEMP_ALBUMARTISTID"
													SayOutput "Delimiter"
												EndIf
												json_select "storeAdamID"
												SayRest
											EndIf

											IfOutput "SectionSong"
												IfNotVar "skipiTunesTags" "true"
													OutputTo "ITUNESARTISTID"
													IfOutput "TEMP_ITUNESARTISTID"
														SayOutput "Delimiter"
													EndIf
													json_select "storeAdamID"
													SayRest
													Set "TEMP_ITUNESARTISTID" "True"
												EndIf
											EndIf

										json_unselect_object
									EndIf

								json_unselect_object
							json_unselect_object
						json_unselect_object
						Else

							IfOutput "SectionAlbum"
								OutputTo "COMPILATION"
								Say "1"
							EndIf

						EndIf

					Else

						IfOutput "SectionSong"

							IfNotVar "naturalTitles" "true"
								OutputTo "ARTIST"
								SayOutput "ALBUMARTIST"
								Say "|"
							EndIf
							IfNotVar "skipiTunesTags" "true"
								OutputTo "ITUNESARTISTID"
								SayOutput "TEMP_ALBUMARTISTID"
								Say "|"
							EndIf
						EndIf

					EndIf
				json_foreach_end

				# Cleanup
				IfOutput "TEMP_ARTIST"
					Set "TEMP_ARTIST"
					OutputTo "ARTIST"
					Say "|"
				EndIf
				IfOutput "TEMP_ITUNESARTISTID"
					Set "TEMP_ITUNESARTISTID"
					IfNotVar "skipiTunesTags" "true"
						OutputTo "ITUNESARTISTID"
						Say "|"
					EndIf
				EndIF

				# Third
				IfOutput "SectionAlbum"

					OutputTo "COPYRIGHT"
					json_select "description"
					IfNot ""
						SayRegexp "[℗©].*"
						If ""
							json_select "description"
							SayRegexp ".*$"
						EndIf
					EndIf

					json_select_object "linkSection"
					IfNot ""
						json_select "title"
						IfNot ""
							json_select_object "link"
								json_select "title"
								OutputTo "TEMP_LINKSECTION"
								SayRest
								json_select_object "segue"
									json_select_object "destination"
										json_select_object "intent"
											json_select_object "contentDescriptor"
												json_select "kind"
												If "recordLabel"
													json_select_object "identifiers"
														IfNotVar "skipiTunesTags" "true"
															OutputTo "ITUNESPUBLISHERID"
															json_select "storeAdamID"
															SayNextNumber
														EndIf
														OutputTo "PUBLISHER"
														SayOutput "TEMP_LINKSECTION"
													json_unselect_object
												EndIf
											json_unselect_object
										json_unselect_object
									json_unselect_object
								json_unselect_object
								Set "TEMP_LINKSECTION"
							json_unselect_object
						EndIf
						json_unselect_object
					EndIf

				EndIf

				IfOutput "SectionSong"

					OutputTo "TRACK"
					json_select "trackNumber"
					SayNextNumber
					Say "|"

					OutputTo "_LENGTH"
					json_select "duration"
					SayNextNumber
					Say "|"

					OutputTo "COMPOSER"
					json_select "composer"
					SayRest
					Say "|"

					OutputTo "DISCNUMBER"
					json_select "discNumber"
					SayNextNumber
					Say "|"

					IfVar "naturalTitles" "true"
						OutputTo "ARTIST"
						json_select "artistName"
						SayRest
						Say "|"
					EndIf

					Set "TOTALDISCS"
					OutputTo "TOTALDISCS"
					json_select "discNumber"
					SayNextNumber

					OutputTo "SHOWMOVEMENT"
    				json_select "workName"
    				IfNot ""
    					Say "1"
                        Say "|"
        				OutputTo "WORK"
        				json_select "workName"
        				SayRest
        				Say "|"
        				OutputTo "WORKDURATION"
        				SayOutput "TEMP_WORK_DURATION"
        				Say "|"
        				OutputTo "MOVEMENTNAME"
        				json_select "title"
        				SayRest
        				Say "|"
        				OutputTo "MOVEMENT"
                        json_foreach_counter
        				SayRest
        				Say "|"
        				OutputTo "MOVEMENTTOTAL"
                        SayOutput "TEMP_LOCAL_ITEMCOUNT"
        				Say "|"
                    Else
                        Say "|"
        				OutputTo "WORK"
        				Say "|"
        				OutputTo "WORKDURATION"
        				Say "|"
        				OutputTo "MOVEMENTNAME"
        				Say "|"
        				OutputTo "MOVEMENT"
        				Say "|"
        				OutputTo "MOVEMENTTOTAL"
        				Say "|"
    				EndIf

    				IfNotVar "skipiTunesTags" "true"
    					OutputTo "ITUNESADVISORY"
    					json_select "showExplicitBadge"
    					IfNot ""
    						Replace "false" "0"
    						Replace "true" "1"
    						Replace "cleaned" "2"
    						Replace "clean" "2"
    						SayRest
    					Else
    						Say "0"
    					EndIf
    					Say "|"
    				EndIf

				EndIf

				Set "SectionAlbum"
				Set "SectionArtist"
				Set "SectionSong"

			json_foreach_end
		EndIf
		Set "ValidSection"
	json_foreach_end
	Else
		Set "NoDataFound" "True"
	EndIf
json_unselect_object

json_select_object "data"
IfNot ""
	json_select_object "seoData"

	json_unselect_object
	EndIf
json_unselect_object

json_select_object "intent"
	IfNot ""
	json_select_object "contentDescriptor"
		json_select_object "locale"
			json_select "storefront"
			Replace "ae" "143481"	# ar
			Replace "ag" "143540"
			Replace "ai" "143538"
			Replace "am" "143524"
			Replace "ar" "143505"	# es
			Replace "at" "143445" # de
			Replace "au" "143460"
			Replace "az" "143568"
			Replace "be" "143446" # nl fr
			Replace "bg" "143526"
			Replace "bh" "143559"
			Replace "bm" "143542"
			Replace "bn" "143560"
			Replace "bo" "143556" # es
			Replace "br" "143503"	# pt
			Replace "bs" "143539"
			Replace "bw" "143525"
			Replace "by" "143565"
			Replace "bz" "143555" # es
			Replace "ca" "143455" # fr
			Replace "ch" "143459" # de fr it
			Replace "cl" "143483" # es
			Replace "cn" "143465" # zh
			Replace "co" "143501" # es
			Replace "cr" "143495" # es
			Replace "cv" "143580"
			Replace "cy" "143557" # tr el
			Replace "cz" "143489" # cs
			Replace "de" "143443" # de
			Replace "dk" "143458" # da
			Replace "dm" "143545"
			Replace "do" "143508" # es
			Replace "ec" "143509" # es
			Replace "ee" "143518"
			Replace "eg" "143516" # ar
			Replace "es" "143454" # ca es
			Replace "fi" "143447" # fi
			Replace "fj" "143583"
			Replace "fm" "143591"
			Replace "fr" "143442" # fr
			Replace "gb" "143444"
			Replace "gd" "143546"
			Replace "gh" "143573"
			Replace "gm" "143584"
			Replace "gr" "143448" # el
			Replace "gt" "143504" # es
			Replace "gw" "143585" # fr
			Replace "hk" "143463" # zh yue
			Replace "hn" "143510" # es
			Replace "hu" "143482" # hu
			Replace "id" "143476" # id
			Replace "ie" "143449"
			Replace "il" "143491" # iw
			Replace "in" "143467" # hi
			Replace "it" "143450" # it
			Replace "jo" "143528" # ar
			Replace "jp" "143462" # ja
			Replace "kh" "143579" # fr
			Replace "kn" "143548"
			Replace "kr" "143466" # ko
			Replace "ky" "143544"
			Replace "la" "143587" # la
			Replace "lb" "143497" # ar
			Replace "lk" "143486"
			Replace "lt" "143520"
			Replace "lu" "143451" # de fr
			Replace "lv" "143519"
			Replace "md" "143523"
			Replace "mn" "143592"
			Replace "mo" "143515" # yue zh
			Replace "mt" "143521"
			Replace "mu" "143533" # fr
			Replace "mx" "143468" # es
			Replace "my" "143473" # ms
			Replace "mz" "143593"
			Replace "na" "143594"
			Replace "ne" "143534" # fr
			Replace "ni" "143512" # es
			Replace "nl" "143452" # nl
			Replace "no" "143457" # nb
			Replace "nz" "143461"
			Replace "om" "143562" # ar
			Replace "pa" "143485"
			Replace "pe" "143507" # es
			Replace "ph" "143474"
			Replace "pl" "143478" # pl
			Replace "pt" "143453" # pt
			Replace "py" "143513" # es
			Replace "qa" "143498" # ar
			Replace "ru" "143469" # uk ru
			Replace "sa" "143479" # ar
			Replace "se" "143456" # sv
			Replace "sg" "143464" # zh
			Replace "si" "143499"
			Replace "sk" "143496" # sk
			Replace "sv" "143506" # es
			Replace "sz" "143602"
			Replace "th" "143475" # th
			Replace "tj" "143603"
			Replace "tm" "143604"
			Replace "tr" "143480" # tr
			Replace "tt" "143551" # fr
			Replace "tw" "143470" # zh
			Replace "ua" "143492" # uk ru
			Replace "ug" "143537"
			Replace "us" "143441" # es
			Replace "ve" "143502" # es
			Replace "vg" "143543"
			Replace "vn" "143471" # vi
			Replace "za" "143472"
			Replace "zw" "143605"
			IfNotVar "skipiTunesTags" "true"
				OutputTo "ITUNESCOUNTRYID"
				SayNextNumber
				json_select "language"
				OutputTo "ITUNESLANGUAGEID"
				SayRest
			EndIf
		json_unselect_object
	json_unselect_object
	EndIf
json_unselect_object

# Cleanup
Set "TEMP_ALBUMARTISTID"
Set "Delimiter"
Set "TEMP_LOCAL_ITEMCOUNT"
Set "TEMP_WORK_DURATION"

IfOutput "NoDataFound"
	Set "Output"
EndIf

json "off"
