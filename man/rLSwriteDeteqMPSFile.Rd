\name{rLSwriteDeteqMPSFile}
\alias{rLSwriteDeteqMPSFile}

\title{Write the deterministic equivalent for the SP model in MPS format.}

\description{
 R interface function for LINDO API function \code{LSwriteDeteqMPSFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSwriteDeteqMPSFile(model,pszFilename,nFormat,iType)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFilename}{Path and name of the MPS file.}
 \item{nFormat}{An integer parameter indicating whether the MPS file is formatted or not. Possible values are:
                   \itemize{
                        \item{LS_FORMATTED_MPS}
                        \item{LS_UNFORMATTED_MPS}
                        \item{LS_FORMATTED_MPS_COMP}
                   }
               }
 \item{iType}{An integer specifying the type of the deterministic equivalent.Possible values are:
                   \itemize{
                        \item{LS_DETEQ_IMPLICIT}
                        \item{LS_DETEQ_EXPLICIT (default)}
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
