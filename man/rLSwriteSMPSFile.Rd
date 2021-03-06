\name{rLSwriteSMPSFile}
\alias{rLSwriteSMPSFile}

\title{Write the CORE,TIME,STOCH files for SP models in SMPS format.}

\description{
 R interface function for LINDO API function \code{LSwriteSMPSFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSwriteSMPSFile(model,pszCorefile,pszTimefile,pszStocfile,nMPStype)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszCorefile}{Path and name of the CORE file in MPS format.}
 \item{pszTimefile}{Path and name of the TIME file.}
 \item{pszStocfile}{Path and name of the STOCH file.}
 \item{nMPStype}{An integer parameter indicating whether the MPS file is formatted or not. Possible values are:
                   \itemize{
                        \item{LS_FORMATTED_MPS}
                        \item{LS_UNFORMATTED_MPS}
                        \item{LS_FORMATTED_MPS_COMP}
                   }
               }
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
